/******************************************************************************
 *
 * Module Name: apdump - Dump routines for ACPI tables (acpidump)
 *
 *****************************************************************************/

/*
 * Copyright (C) 2000 - 2015, Intel Corp.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions, and the following disclaimer,
 *    without modification.
 * 2. Redistributions in binary form must reproduce at minimum a disclaimer
 *    substantially similar to the "NO WARRANTY" disclaimer below
 *    ("Disclaimer") and any redistribution must be conditioned upon
 *    including a substantially similar Disclaimer requirement for further
 *    binary redistribution.
 * 3. Neither the names of the above-listed copyright holders nor the names
 *    of any contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * Alternatively, this software may be distributed under the terms of the
 * GNU General Public License ("GPL") version 2 as published by the Free
 * Software Foundation.
 *
 * NO WARRANTY
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDERS OR CONTRIBUTORS BE LIABLE FOR SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGES.
 */

#include "acpidump.h"

/* Local prototypes */

static int
ap_dump_table_buffer(struct acpi_table_header *table,
                     u32 instance, acpi_physical_address address);

/******************************************************************************
 *
 * FUNCTION:    ap_is_valid_header
 *
 * PARAMETERS:  table               - Pointer to table to be validated
 *
 * RETURN:      TRUE if the header appears to be valid. FALSE otherwise
 *
 * DESCRIPTION: Check for a valid ACPI table header
 *
 ******************************************************************************/

u8 ap_is_valid_header(struct acpi_table_header *table)
{

    if (!ACPI_VALIDATE_RSDP_SIG(table->signature)) {

        /* Make sure signature is all ASCII and a valid ACPI name */

        if (!acpi_ut_valid_acpi_name(table->signature)) {
            acpi_log_error("Table signature (0x%8.8X) is invalid\n",
                           *(u32 *)table->signature);
            return (FALSE);
        }

        /* Check for minimum table length */

        if (table->length < sizeof(struct acpi_table_header)) {
            acpi_log_error("Table length (0x%8.8X) is invalid\n",
                           table->length);
            return (FALSE);
        }
    }

    return (TRUE);
}

/******************************************************************************
 *
 * FUNCTION:    ap_is_valid_checksum
 *
 * PARAMETERS:  table               - Pointer to table to be validated
 *
 * RETURN:      TRUE if the checksum appears to be valid. FALSE otherwise.
 *
 * DESCRIPTION: Check for a valid ACPI table checksum.
 *
 ******************************************************************************/

u8 ap_is_valid_checksum(struct acpi_table_header *table)
{
    acpi_status status;
    struct acpi_table_rsdp *rsdp;

    if (ACPI_VALIDATE_RSDP_SIG(table->signature)) {
        /*
         * Checksum for RSDP.
         * Note: Other checksums are computed during the table dump.
         */
        rsdp = ACPI_CAST_PTR(struct acpi_table_rsdp, table);
        status = acpi_tb_validate_rsdp(rsdp);
    } else {
        status = acpi_tb_verify_checksum(table, table->length);
    }

    if (ACPI_FAILURE(status)) {
        acpi_log_error("%4.4s: Warning: wrong checksum in table\n",
                       table->signature);
    }

    return (AE_OK);
}

/******************************************************************************
 *
 * FUNCTION:    ap_get_table_length
 *
 * PARAMETERS:  table               - Pointer to the table
 *
 * RETURN:      Table length
 *
 * DESCRIPTION: Obtain table length according to table signature.
 *
 ******************************************************************************/

u32 ap_get_table_length(struct acpi_table_header *table)
{
    struct acpi_table_rsdp *rsdp;

    /* Check if table is valid */

    if (!ap_is_valid_header(table)) {
        return (0);
    }

    if (ACPI_VALIDATE_RSDP_SIG(table->signature)) {
        rsdp = ACPI_CAST_PTR(struct acpi_table_rsdp, table);
        return (acpi_tb_get_rsdp_length(rsdp));
    }

    /* Normal ACPI table */

    return (table->length);
}

/******************************************************************************
 *
 * FUNCTION:    ap_dump_table_buffer
 *
 * PARAMETERS:  table               - ACPI table to be dumped
 *              instance            - ACPI table instance no. to be dumped
 *              address             - Physical address of the table
 *
 * RETURN:      None
 *
 * DESCRIPTION: Dump an ACPI table in standard ASCII hex format, with a
 *              header that is compatible with the acpi_xtract utility.
 *
 ******************************************************************************/

static int
ap_dump_table_buffer(struct acpi_table_header *table,
                     u32 instance, acpi_physical_address address)
{
    u32 table_length;

    table_length = ap_get_table_length(table);

    /* Print only the header if requested */

    if (gbl_summary_mode) {
        acpi_tb_print_table_header(address, table);
        return (0);
    }

    /* Dump to binary file if requested */

    if (gbl_binary_mode) {
        return (ap_write_to_binary_file(table, instance));
    }

    /*
     * Dump the table with header for use with acpixtract utility.
     * Note: simplest to just always emit a 64-bit address. acpi_xtract
     * utility can handle this.
     */
    acpi_ut_file_printf(gbl_output_file, "%4.4s @ 0x%8.8X%8.8X\n",
                        table->signature, ACPI_FORMAT_UINT64(address));

    acpi_ut_dump_buffer_to_file(gbl_output_file,
                                ACPI_CAST_PTR(u8, table), table_length,
                                DB_BYTE_DISPLAY, 0);
    acpi_ut_file_printf(gbl_output_file, "\n");
    return (0);
}

/******************************************************************************
 *
 * FUNCTION:    ap_dump_all_tables
 *
 * PARAMETERS:  None
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Get all tables from the RSDT/XSDT (or at least all of the
 *              tables that we can possibly get).
 *
 ******************************************************************************/

int ap_dump_all_tables(void)
{
    struct acpi_table_header *table;
    u32 instance = 0;
    acpi_physical_address address;
    acpi_status status;
    int table_status;
    u32 i;

    /* Get and dump all available ACPI tables */

    for (i = 0; i < AP_MAX_ACPI_FILES; i++) {
        status =
            acpi_os_get_table_by_index(i, &table, &instance, &address);
        if (ACPI_FAILURE(status)) {

            /* AE_LIMIT means that no more tables are available */

            if (status == AE_LIMIT) {
                return (0);
            } else if (i == 0) {
                acpi_log_error
                ("Could not get ACPI tables, %s\n",
                 acpi_format_exception(status));
                return (-1);
            } else {
                acpi_log_error
                ("Could not get ACPI table at index %u, %s\n",
                 i, acpi_format_exception(status));
                continue;
            }
        }

        table_status = ap_dump_table_buffer(table, instance, address);
        ACPI_FREE(table);

        if (table_status) {
            break;
        }
    }

    /* Something seriously bad happened if the loop terminates here */

    return (-1);
}

/******************************************************************************
 *
 * FUNCTION:    ap_dump_table_by_address
 *
 * PARAMETERS:  ascii_address       - Address for requested ACPI table
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Get an ACPI table via a physical address and dump it.
 *
 ******************************************************************************/

int ap_dump_table_by_address(char *ascii_address)
{
    acpi_physical_address address;
    struct acpi_table_header *table;
    acpi_status status;
    int table_status;
    u64 long_address;

    /* Convert argument to an integer physical address */

    status = acpi_ut_strtoul64(ascii_address, 0, &long_address);
    if (ACPI_FAILURE(status)) {
        acpi_log_error("%s: Could not convert to a physical address\n",
                       ascii_address);
        return (-1);
    }

    address = (acpi_physical_address) long_address;
    status = acpi_os_get_table_by_address(address, &table);
    if (ACPI_FAILURE(status)) {
        acpi_log_error("Could not get table at 0x%8.8X%8.8X, %s\n",
                       ACPI_FORMAT_UINT64(address),
                       acpi_format_exception(status));
        return (-1);
    }

    table_status = ap_dump_table_buffer(table, 0, address);
    ACPI_FREE(table);
    return (table_status);
}

/******************************************************************************
 *
 * FUNCTION:    ap_dump_table_by_name
 *
 * PARAMETERS:  signature           - Requested ACPI table signature
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Get an ACPI table via a signature and dump it. Handles
 *              multiple tables with the same signature (SSDTs).
 *
 ******************************************************************************/

int ap_dump_table_by_name(char *signature)
{
    char local_signature[ACPI_NAME_SIZE + 1];
    u32 instance;
    struct acpi_table_header *table;
    acpi_physical_address address;
    acpi_status status;
    int table_status;

    if (ACPI_STRLEN(signature) != ACPI_NAME_SIZE) {
        acpi_log_error
        ("Invalid table signature [%s]: must be exactly 4 characters\n",
         signature);
        return (-1);
    }

    /* Table signatures are expected to be uppercase */

    ACPI_STRCPY(local_signature, signature);
    acpi_ut_strupr(local_signature);

    /* To be friendly, handle tables whose signatures do not match the name */

    if (ACPI_COMPARE_NAME(local_signature, "FADT")) {
        ACPI_STRCPY(local_signature, ACPI_SIG_FADT);
    } else if (ACPI_COMPARE_NAME(local_signature, "MADT")) {
        ACPI_STRCPY(local_signature, ACPI_SIG_MADT);
    }

    /* Dump all instances of this signature (to handle multiple SSDTs) */

    for (instance = 0; instance < AP_MAX_ACPI_FILES; instance++) {
        status = acpi_os_get_table_by_name(local_signature, instance,
                                           &table, &address);
        if (ACPI_FAILURE(status)) {

            /* AE_LIMIT means that no more tables are available */

            if (status == AE_LIMIT) {
                return (0);
            }

            acpi_log_error
            ("Could not get ACPI table with signature [%s], %s\n",
             local_signature, acpi_format_exception(status));
            return (-1);
        }

        table_status = ap_dump_table_buffer(table, instance, address);
        ACPI_FREE(table);

        if (table_status) {
            break;
        }
    }

    /* Something seriously bad happened if the loop terminates here */

    return (-1);
}

/******************************************************************************
 *
 * FUNCTION:    ap_dump_table_from_file
 *
 * PARAMETERS:  pathname            - File containing the binary ACPI table
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Dump an ACPI table from a binary file
 *
 ******************************************************************************/

int ap_dump_table_from_file(char *pathname)
{
    struct acpi_table_header *table;
    u32 file_size = 0;
    int table_status = -1;

    /* Get the entire ACPI table from the file */

    table = ap_get_table_from_file(pathname, &file_size);
    if (!table) {
        return (-1);
    }

    /* File must be at least as long as the table length */

    if (table->length > file_size) {
        acpi_log_error
        ("Table length (0x%X) is too large for input file (0x%X) %s\n",
         table->length, file_size, pathname);
        goto exit;
    }

    if (gbl_verbose_mode) {
        acpi_log_error
        ("Input file:  %s contains table [%4.4s], 0x%X (%u) bytes\n",
         pathname, table->signature, file_size, file_size);
    }

    table_status = ap_dump_table_buffer(table, 0, 0);

exit:
    ACPI_FREE(table);
    return (table_status);
}
