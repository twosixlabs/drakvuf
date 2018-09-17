/*********************IMPORTANT DRAKVUF LICENSE TERMS***********************
 *                                                                         *
 * DRAKVUF (C) 2014-2018 Tamas K Lengyel.                                  *
 * Tamas K Lengyel is hereinafter referred to as the author.               *
 * This program is free software; you may redistribute and/or modify it    *
 * under the terms of the GNU General Public License as published by the   *
 * Free Software Foundation; Version 2 ("GPL"), BUT ONLY WITH ALL OF THE   *
 * CLARIFICATIONS AND EXCEPTIONS DESCRIBED HEREIN.  This guarantees your   *
 * right to use, modify, and redistribute this software under certain      *
 * conditions.  If you wish to embed DRAKVUF technology into proprietary   *
 * software, alternative licenses can be aquired from the author.          *
 *                                                                         *
 * Note that the GPL places important restrictions on "derivative works",  *
 * yet it does not provide a detailed definition of that term.  To avoid   *
 * misunderstandings, we interpret that term as broadly as copyright law   *
 * allows.  For example, we consider an application to constitute a        *
 * derivative work for the purpose of this license if it does any of the   *
 * following with any software or content covered by this license          *
 * ("Covered Software"):                                                   *
 *                                                                         *
 * o Integrates source code from Covered Software.                         *
 *                                                                         *
 * o Reads or includes copyrighted data files.                             *
 *                                                                         *
 * o Is designed specifically to execute Covered Software and parse the    *
 * results (as opposed to typical shell or execution-menu apps, which will *
 * execute anything you tell them to).                                     *
 *                                                                         *
 * o Includes Covered Software in a proprietary executable installer.  The *
 * installers produced by InstallShield are an example of this.  Including *
 * DRAKVUF with other software in compressed or archival form does not     *
 * trigger this provision, provided appropriate open source decompression  *
 * or de-archiving software is widely available for no charge.  For the    *
 * purposes of this license, an installer is considered to include Covered *
 * Software even if it actually retrieves a copy of Covered Software from  *
 * another source during runtime (such as by downloading it from the       *
 * Internet).                                                              *
 *                                                                         *
 * o Links (statically or dynamically) to a library which does any of the  *
 * above.                                                                  *
 *                                                                         *
 * o Executes a helper program, module, or script to do any of the above.  *
 *                                                                         *
 * This list is not exclusive, but is meant to clarify our interpretation  *
* of derived works with some common examples.  Other people may interpret *
 * the plain GPL differently, so we consider this a special exception to   *
 * the GPL that we apply to Covered Software.  Works which meet any of     *
 * these conditions must conform to all of the terms of this license,      *
 * particularly including the GPL Section 3 requirements of providing      *
 * source code and allowing free redistribution of the work as a whole.    *
 *                                                                         *
 * Any redistribution of Covered Software, including any derived works,    *
 * must obey and carry forward all of the terms of this license, including *
 * obeying all GPL rules and restrictions.  For example, source code of    *
 * the whole work must be provided and free redistribution must be         *
 * allowed.  All GPL references to "this License", are to be treated as    *
 * including the terms and conditions of this license text as well.        *
 *                                                                         *
 * Because this license imposes special exceptions to the GPL, Covered     *
 * Work may not be combined (even as part of a larger work) with plain GPL *
 * software.  The terms, conditions, and exceptions of this license must   *
 * be included as well.  This license is incompatible with some other open *
 * source licenses as well.  In some cases we can relicense portions of    *
 * DRAKVUF or grant special permissions to use it in other open source     *
 * software.  Please contact tamas.k.lengyel@gmail.com with any such       *
 * requests.  Similarly, we don't incorporate incompatible open source     *
 * software into Covered Software without special permission from the      *
 * copyright holders.                                                      *
 *                                                                         *
 * If you have any questions about the licensing restrictions on using     *
 * DRAKVUF in other works, are happy to help.  As mentioned above,         *
 * alternative license can be requested from the author to integrate       *
 * DRAKVUF into proprietary applications and appliances.  Please email     *
 * tamas.k.lengyel@gmail.com for further information.                      *
 *                                                                         *
 * If you have received a written license agreement or contract for        *
 * Covered Software stating terms other than these, you may choose to use  *
 * and redistribute Covered Software under those terms instead of these.   *
 *                                                                         *
 * Source is provided to this software because we believe users have a     *
 * right to know exactly what a program is going to do before they run it. *
 * This also allows you to audit the software for security holes.          *
 *                                                                         *
 * Source code also allows you to port DRAKVUF to new platforms, fix bugs, *
 * and add new features.  You are highly encouraged to submit your changes *
 * on https://github.com/tklengyel/drakvuf, or by other methods.           *
 * By sending these changes, it is understood (unless you specify          *
 * otherwise) that you are offering unlimited, non-exclusive right to      *
 * reuse, modify, and relicense the code.  DRAKVUF will always be          *
 * available Open Source, but this is important because the inability to   *
 * relicense code has caused devastating problems for other Free Software  *
 * projects (such as KDE and NASM).                                        *
 * To specify special license conditions of your contributions, just say   *
 * so when you send them.                                                  *
 *                                                                         *
 * This program is distributed in the hope that it will be useful, but     *
 * WITHOUT ANY WARRANTY; without even the implied warranty of              *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the DRAKVUF   *
 * license file for more details (it's in a COPYING file included with     *
 * DRAKVUF, and also available from                                        *
 * https://github.com/tklengyel/drakvuf/COPYING)                           *
 *                                                                         *
 ***************************************************************************/

#ifndef OVMFMON_PRIVATE_H
#define OVMFMON_PRIVATE_H

/*
 * Static info from xen/tools/firmware/hvmloader/ovmf.c
 */
#define OVMF_MAXOFFSET          0x000FFFFFULL
#define OVMF_END                0x100000000ULL
#define LOWCHUNK_BEGIN          0x000F0000
#define LOWCHUNK_SIZE           0x00010000
#define LOWCHUNK_MAXOFFSET      0x0000FFFF
#define OVMF_INFO_PHYSICAL_ADDRESS 0x00001000
#define OVMF_INFO_MAX_TABLES 4
#define PAGE_SIZE               (1u<<12)

struct ovmf_info {
    char signature[14]; /* XenHVMOVMF\0\0\0\0 */
    uint8_t length;     /* Length of this struct */
    uint8_t checksum;   /* Set such that the sum over bytes 0..length == 0 */
    /*
     * Physical address of an array of tables_nr elements.
     *
     * Each element is a 64 bit value containing the physical address
     * of a BIOS table.
     */
    uint64_t tables;
    uint32_t tables_nr;
    /*
     * Physical address of the e820 table, contains e820_nr entries.
     */
    uint64_t e820;
    uint32_t e820_nr;
} __attribute__ ((packed));

#define EFI_FVH_SIGNATURE 0x4856465f // _FVH

typedef struct {
    uint32_t  Data1;
    uint16_t  Data2;
    uint16_t  Data3;
    uint8_t   Data4[8];
}  __attribute__ ((packed)) EFI_GUID;

typedef struct {
    ///
    /// The first 16 bytes are reserved to allow for the reset vector of
    /// processors whose reset vector is at address 0.
    ///
    uint8_t                     ZeroVector[16];
    ///
    /// Declares the file system with which the firmware volume is formatted.
    ///
    EFI_GUID                    FileSystemGuid;
    ///
    /// Length in bytes of the complete firmware volume, including the header.
    ///
    uint64_t                    FvLength;
    ///
    /// Set to EFI_FVH_SIGNATURE
    ///
    uint32_t                    Signature;
    ///
    /// Declares capabilities and power-on defaults for the firmware volume.
    ///
    uint32_t                    Attributes;
    ///
    /// Length in bytes of the complete firmware volume header.
    ///
    uint16_t                    HeaderLength;
    ///
    /// A 16-bit checksum of the firmware volume header. A valid header sums to zero.
    ///
    uint16_t                    Checksum;
    ///
    /// Offset, relative to the start of the header, of the extended header
    /// (EFI_FIRMWARE_VOLUME_EXT_HEADER) or zero if there is no extended header.
    ///
    uint16_t                    ExtHeaderOffset;
    ///
    /// This field must always be set to zero.
    ///
    uint8_t                     Reserved[1];
    ///
    /// Set to 2. Future versions of this specification may define new header fields and will
    /// increment the Revision field accordingly.
    ///
    uint8_t                     Revision;
    ///
    /// An array of run-length encoded FvBlockMapEntry structures. The array is
    /// terminated with an entry of {(uint32_t)0,(uint32_t)0}.
    ///
    uint64_t    BlockMap[1];
}  __attribute__ ((packed)) EFI_FIRMWARE_VOLUME_HEADER;

struct function {
    const char *name;
    addr_t address;
};

struct module {
    const char *name;
    addr_t BaseAddress;
    addr_t EntryPoint;
    addr_t textbaseaddress;
    addr_t databaseaddress;
    addr_t fcount;
    struct function function[150];
};

struct module modules[] = {
    { .name = "SecMain", .BaseAddress=0x00fffcc094, .EntryPoint=0x00fffd02d4, .textbaseaddress=0x00fffcc2d4, .databaseaddress=0x00fffd1314, .fcount = 41, .function =
        {
            { .name="SzFree", .address=0x240 },{ .name="SerialPortWrite", .address=0x241 },{ .name="AsciiStrLen", .address=0x97b },{ .name="SzAlloc", .address=0x443 },{ .name="GetApicMode.part.2", .address=0x49c },{ .name="LocalApicBaseAddressMsrSupported", .address=0x4e9 },{ .name="GetLocalApicBaseAddress", .address=0x526 },{ .name="LzmaGuidedSectionExtraction", .address=0x1077 },{ .name="LzmaGuidedSectionGetInfo", .address=0x1158 },{ .name="TemporaryRamMigration", .address=0x33cf },{ .name="FindFfsSectionInstance", .address=0x1856 },{ .name="LzmaDec_TryDummy.lto_priv.21", .address=0x1980 },{ .name="AsciiStrnLenS", .address=0x39e },{ .name="GetDecodedSizeOfBuf", .address=0x34a },{ .name="LzmaUefiDecompress", .address=0xbb6 },{ .name="InternalAssertJumpBuffer", .address=0xa83 },{ .name="DebugPrintEnabled", .address=0x344 },{ .name="DebugAssert", .address=0x3eb },{ .name="GetInterruptState", .address=0x394 },{ .name="ReadUnaligned64", .address=0x90d },{ .name="BasePrintLibSPrintMarker.constprop.18", .address=0x3495 },{ .name="SecCoreStartupWithStack", .address=0x12a3 },{ .name="BasePrintLibFillBuffer", .address=0x366 },{ .name="ReadLocalApicReg", .address=0x64d },{ .name="AsciiSPrint.constprop.16", .address=0x339f },{ .name="ReadUnaligned16", .address=0x944 },{ .name="GetExtractGuidedSectionHandlerInfo", .address=0x2f3 },{ .name="FindFfsFileAndSection", .address=0x18ad },{ .name="LzmaDec_DecodeReal2.lto_priv.22", .address=0x1f68 },{ .name="LzmaDec_WriteRem.lto_priv.20", .address=0x279 },{ .name="DebugPrint", .address=0x9f5 },{ .name="CpuDeadLoop", .address=0x3cf },{ .name="CompareGuid", .address=0xad9 },{ .name="IoRead32", .address=0x897 },{ .name="WriteLocalApicReg", .address=0x55e },{ .name="PeCoffLoaderGetPdbPointer", .address=0x716 },{ .name="IoWrite32", .address=0x85a },{ .name="BasePrintLibSPrint.constprop.19", .address=0x4055 },{ .name="DebugAssertEnabled", .address=0x347 },{ .name="SetInterruptState", .address=0x3c4 },{ .name="CopyMem", .address=0xb26 },{ .name="WriteUnaligned64", .address=0x8ce },{ .name="SecStartupPhase2", .address=0x2c08 }
        },
    },
};

#endif
