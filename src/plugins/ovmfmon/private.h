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
    struct function functions[150];
};

struct module modules[] = {
    { .name = "SecMain", .BaseAddress=0x00fffcc094, .EntryPoint=0x00fffd0334, .textbaseaddress=0x0000820380, .databaseaddress=0x000082bac0, .fcount = 41, .functions =
        {
            { .name="SzFree", .address=0x240 },{ .name="SzAlloc", .address=0x40c },{ .name="GetApicMode.part.2", .address=0x465 },{ .name="LocalApicBaseAddressMsrSupported", .address=0x4b2 },{ .name="GetLocalApicBaseAddress", .address=0x4ef },{ .name="LzmaGuidedSectionExtraction", .address=0x225c },{ .name="LzmaGuidedSectionGetInfo", .address=0x233d },{ .name="TemporaryRamMigration", .address=0x330d },{ .name="FindFfsSectionInstance", .address=0x2a1c },{ .name="LzmaDec_TryDummy.lto_priv.21", .address=0xfd4 },{ .name="AsciiStrnLenS", .address=0x366 },{ .name="GetDecodedSizeOfBuf", .address=0x312 },{ .name="LzmaUefiDecompress", .address=0xb13 },{ .name="InternalAssertJumpBuffer", .address=0x9e0 },{ .name="DebugPrintEnabled", .address=0x30c },{ .name="DebugAssert", .address=0x3b3 },{ .name="GetInterruptState", .address=0x35c },{ .name="ReadUnaligned64", .address=0x972 },{ .name="BasePrintLibSPrintMarker.constprop.18", .address=0x33d3 },{ .name="SecCoreStartupWithStack", .address=0x2488 },{ .name="BasePrintLibFillBuffer", .address=0x32e },{ .name="ReadLocalApicReg", .address=0x616 },{ .name="AsciiSPrint.constprop.16", .address=0x32dd },{ .name="ReadUnaligned16", .address=0x9a9 },{ .name="GetExtractGuidedSectionHandlerInfo", .address=0x2bb },{ .name="FindFfsFileAndSection", .address=0x2a73 },{ .name="LzmaDec_DecodeReal2.lto_priv.22", .address=0x15bc },{ .name="LzmaDec_WriteRem.lto_priv.20", .address=0x241 },{ .name="DebugPrint", .address=0x823 },{ .name="CpuDeadLoop", .address=0x397 },{ .name="CompareGuid", .address=0xa36 },{ .name="IoRead32", .address=0x8fc },{ .name="WriteLocalApicReg", .address=0x527 },{ .name="PeCoffLoaderGetPdbPointer", .address=0x6df },{ .name="IoWrite32", .address=0x8bf },{ .name="BasePrintLibSPrint.constprop.19", .address=0x3f93 },{ .name="DebugAssertEnabled", .address=0x30f },{ .name="SetInterruptState", .address=0x38c },{ .name="CopyMem", .address=0xa83 },{ .name="WriteUnaligned64", .address=0x933 },{ .name="SecStartupPhase2", .address=0x2b46 }
        },
    },
    { .name = "PeiCore", .BaseAddress=0x0000820140, .EntryPoint=0x0000822759, .textbaseaddress=0x0000820380, .databaseaddress=0x000082bac0, .fcount = 137, .functions =
        {
            { .name="PlatformDebugLibIoPortFound", .address=0x1bd8 },{ .name="WriteUnaligned64", .address=0x2978 },{ .name="ReportStatusCodeEx.constprop.16", .address=0x4fb4 },{ .name="InternalBuildMemoryAllocationHob", .address=0x6c89 },{ .name="UpdateOrSplitMemoryAllocationHob", .address=0x6d7a },{ .name="ConvertPointer", .address=0x8ec2 },{ .name="ReadUnaligned32", .address=0x2a79 },{ .name="BasePrintLibSPrint.constprop.33", .address=0x9760 },{ .name="InternalPeiCreateHob", .address=0x2d0d },{ .name="PeiGetBootMode", .address=0x7c85 },{ .name="PeiLocatePpi", .address=0x8ee3 },{ .name="BasePrintLibSPrintMarker.constprop.32", .address=0x4207 },{ .name="PeiFfsFvPpiGetFileInfo2", .address=0x8a18 },{ .name="ReportStatusCodeWithExtendedData.constprop.15", .address=0x505c },{ .name="LShiftU64", .address=0x2ae6 },{ .name="PeiDefaultMemWrite", .address=0x7c2b },{ .name="AsciiStrnLenS", .address=0x257f },{ .name="PeiDefaultMemRead32", .address=0x7bfb },{ .name="PeiFfsFvPpiFindFileByType", .address=0x8dcf },{ .name="SecurityPpiNotifyCallback", .address=0x8fa8 },{ .name="AsciiSPrint.constprop.30", .address=0x4dcf },{ .name="PeiFfsFvPpiGetVolumeInfo", .address=0x8c04 },{ .name="PeiFfsFvPpiGetFileInfo", .address=0x8877 },{ .name="PeiLoadImage.constprop.12", .address=0x5202 },{ .name="ConvertPointerInRanges", .address=0x9601 },{ .name="PeiFfsFindNextFile", .address=0x56fc },{ .name="PeiFfsGetFileInfo2", .address=0x54c3 },{ .name="PeiServicesLocatePpi", .address=0x2c7b },{ .name="InternalReportStatusCode.part.2.constprop.18", .address=0x4f5a },{ .name="DebugPrintEnabled", .address=0x254b },{ .name="PeiInstallPeiMemory", .address=0x66b8 },{ .name="PeiFfsFindSectionData", .address=0x562b },{ .name="PeiServicesReInstallPpi", .address=0x2cbf },{ .name="DebugAssert", .address=0x25c1 },{ .name="FirmwareVolmeInfoPpiNotifyCallback", .address=0x67b0 },{ .name="FileHandleToVolume", .address=0x7224 },{ .name="PeiFfsGetVolumeInfo", .address=0x53ee },{ .name="ReadUnaligned64", .address=0x29b7 },{ .name="PeiDefaultMemRead16", .address=0x7c01 },{ .name="ReportStatusCode", .address=0x24f4 },{ .name="PeiGetHobList", .address=0x6548 },{ .name="ProcessLibraryConstructorList.constprop.7", .address=0x975f },{ .name="BasePrintLibFillBuffer", .address=0x2551 },{ .name="PeiDefaultMemWrite8", .address=0x7bf1 },{ .name="PeiFfsFvPpiFindSectionByType", .address=0x8bde },{ .name="FindNextCoreFvHandle", .address=0x8de6 },{ .name="PeiDefaultIoRead8", .address=0x7c04 },{ .name="ZeroMem", .address=0x287f },{ .name="PeiResetSystem", .address=0x91d3 },{ .name="GetNextHob", .address=0x28ee },{ .name="PeCoffLoaderGetMachineType", .address=0x2625 },{ .name="MigrateMemoryPages", .address=0x72e4 },{ .name="PeimDispatchReadiness", .address=0x8226 },{ .name="PeiDefaultMemWrite16", .address=0x7bef },{ .name="PeiCheckAndSwitchStack", .address=0x7454 },{ .name="ReadUnaligned16", .address=0x2aaf },{ .name="PeiDefaultMemWrite32", .address=0x7bed },{ .name="ReportProgressCodeEnabled", .address=0x24f1 },{ .name="PeCoffLoaderImageAddress", .address=0x1bfe },{ .name="ReportDebugCodeEnabled", .address=0x24eb },{ .name="PeiDefaultMemWrite64", .address=0x7beb },{ .name="PeiResetSystem2", .address=0x9170 },{ .name="PeiDefaultMemRead64", .address=0x7bf5 },{ .name="PeiDefaultIoWrite", .address=0x7c15 },{ .name="PeiFfsFvPpiProcessVolume", .address=0x851d },{ .name="PeiCore", .address=0x240 },{ .name="PeiFreePages", .address=0x6dd5 },{ .name="AllocateCopyPool.constprop.27", .address=0x4dff },{ .name="PeiImageRead", .address=0x678f },{ .name="PeiReportStatusCode", .address=0x9100 },{ .name="DebugPrint", .address=0x2684 },{ .name="PeiDefaultIoRead16", .address=0x7bfe },{ .name="ThirdPartyFvPpiNotifyCallback", .address=0x856a },{ .name="CpuDeadLoop", .address=0x25a5 },{ .name="PeiDefaultMemRead8", .address=0x7c07 },{ .name="PeiFfsFvPpiFindFileByName", .address=0x8cb6 },{ .name="ProcessNotifyList", .address=0x95a2 },{ .name="PeiRegisterForShadow", .address=0x7ce7 },{ .name="CompareGuid", .address=0x29ee },{ .name="PeiServicesInstallPpi", .address=0x2ceb },{ .name="PeiDefaultPciCfg2Write", .address=0x7bdf },{ .name="PeCoffLoaderGetPeHeaderMagicValue", .address=0x1c1e },{ .name="PeiServicesNotifyPpi", .address=0x2c59 },{ .name="PeiNotifyPpi", .address=0x9405 },{ .name="InternalPeiNotifyPpi.part.3", .address=0x923f },{ .name="InternalPeiInstallPpi.part.1", .address=0x942a },{ .name="PeCoffLoaderGetImageInfo.part.0", .address=0x1c37 },{ .name="CopyGuid", .address=0x2a3b },{ .name="_ModuleEntryPoint", .address=0x2619 },{ .name="ReportErrorCodeEnabled", .address=0x24ee },{ .name="PeiDefaultIoRead", .address=0x7c20 },{ .name="PeiFfsGetFileInfo", .address=0x5540 },{ .name="PeiDefaultIoWrite32", .address=0x7bec },{ .name="SetMem", .address=0x2820 },{ .name="PeiAllocatePages", .address=0x6f72 },{ .name="SwitchStack.constprop.26", .address=0x4e7e },{ .name="CopyMem.part.0", .address=0x2787 },{ .name="VerifyPeim", .address=0x96b3 },{ .name="FindFileEx.constprop.0", .address=0x7d70 },{ .name="GetPeiServicesTablePointer", .address=0x2bdd },{ .name="PeiServicesAllocatePages", .address=0x2c24 },{ .name="PeiDefaultPciCfg2Read", .address=0x7bd4 },{ .name="CalculateSum8", .address=0x2b29 },{ .name="PeiReInstallPpi", .address=0x8fff },{ .name="IsPpiInstalled.constprop.11", .address=0x9718 },{ .name="DispatchNotify.constprop.13", .address=0x50bd },{ .name="PeiDefaultIoRead64", .address=0x7bf2 },{ .name="GetFirstHob", .address=0x2dfa },{ .name="DebugAssertEnabled", .address=0x254e },{ .name="PeiDefaultIoWrite64", .address=0x7bea },{ .name="PeiCreateHob", .address=0x65a8 },{ .name="PeiDefaultMemRead", .address=0x7c0a },{ .name="ProcessFvFile", .address=0x574f },{ .name="PeiLoadImageLoadImage.constprop.1", .address=0x30af },{ .name="GetHobList", .address=0x2d75 },{ .name="PeiDefaultPciCfg2Modify", .address=0x7bc9 },{ .name="ProcessSection", .address=0x5fd0 },{ .name="PeiFfsFindNextVolume", .address=0x567e },{ .name="PeiDefaultIoWrite16", .address=0x7bee },{ .name="FvHandleToCoreHandle", .address=0x8e3d },{ .name="AllocateZeroPool", .address=0x2e51 },{ .name="PeiCoreEntry", .address=0x7446 },{ .name="PeiFfsFindSectionData3", .address=0x55a1 },{ .name="PeiAllocatePool", .address=0x6bb9 },{ .name="CopyMem", .address=0x2812 },{ .name="PeiDefaultIoWrite8", .address=0x7bf0 },{ .name="InternalPeiServicesInstallFvInfoPpi", .address=0x2e7b },{ .name="SetPeiServicesTablePointer", .address=0x2b96 },{ .name="AllocatePool", .address=0x2e16 },{ .name="PeiInstallPpi", .address=0x957d },{ .name="PeiFfsFindFileByName", .address=0x544f },{ .name="PeiSetBootMode", .address=0x7c36 },{ .name="PeiDefaultIoRead32", .address=0x7bf8 },{ .name="InternalCheckFvAlignment", .address=0x271f },{ .name="PeiFfsFvPpiFindSectionByType2", .address=0x8a80 },{ .name="PeiLoadImageLoadImageWrapper", .address=0x6c55 },{ .name="AsmReadIdtr", .address=0x2941 }
        }
    },
    { .name = "PlatformPei", .BaseAddress=0x00008352c0, .EntryPoint=0x0000835500, .textbaseaddress=0x0000835500, .databaseaddress=0x000083d300, .fcount = 74, .functions =
        {
            { .name="PlatformDebugLibIoPortFound", .address=0x31a7 },{ .name="SwapBytes32", .address=0x31cd },{ .name="WriteUnaligned64", .address=0x3668 },{ .name="AsciiStrLen", .address=0x3715 },{ .name="InternalQemuFwCfgReadBytes", .address=0x3899 },{ .name="WriteFeatureControl", .address=0x40bf },{ .name="InternalPeiCreateHob", .address=0x3a74 },{ .name="BasePrintLibSPrintMarker.constprop.30", .address=0x4eac },{ .name="GetVariableMtrrCountWorker", .address=0x60cc },{ .name="LShiftU64", .address=0x3813 },{ .name="MtrrLibGetNumberOfTypes", .address=0x5cca },{ .name="LibPcdSetBoolS", .address=0x3b96 },{ .name="QemuFwCfgSelectItem", .address=0x33e5 },{ .name="AsciiStrnLenS", .address=0x329a },{ .name="GetNamedFwCfgBoolean", .address=0x4185 },{ .name="AsciiStrCmp", .address=0x3796 },{ .name="LibPcdSet32S", .address=0x3bed },{ .name="MtrrGetVariableMtrrWorker.constprop.6", .address=0x6148 },{ .name="MtrrLibCalculateSubtractivePath", .address=0x4a01 },{ .name="RShiftU64", .address=0x3856 },{ .name="OnMpServicesAvailable.lto_priv.34", .address=0x40d5 },{ .name="AddMemoryBaseSizeHob", .address=0x4262 },{ .name="DebugPrintEnabled", .address=0x3266 },{ .name="DebugAssert", .address=0x32f2 },{ .name="ReadUnaligned64", .address=0x36a7 },{ .name="MtrrLibGetRawVariableRanges", .address=0x5ffb },{ .name="PciCf8Read16", .address=0x352b },{ .name="AddIoMemoryBaseSizeHob", .address=0x427d },{ .name="MtrrLibAppendVariableMtrr", .address=0x5abc },{ .name="GetPcdPpiPointer", .address=0x3afe },{ .name="BasePrintLibFillBuffer", .address=0x326c },{ .name="MtrrLibLowestType", .address=0x5a6c },{ .name="BuildMemoryAllocationHob", .address=0x3f88 },{ .name="BasePrintLibSPrint.constprop.31", .address=0x61d1 },{ .name="ZeroMem", .address=0x3e10 },{ .name="GetSystemMemorySizeAbove4gb.lto_priv.36", .address=0x429b },{ .name="ReadUnaligned16", .address=0x36de },{ .name="ScanOrAdd64BitE820Ram.lto_priv.37", .address=0x430b },{ .name="QemuFwCfgRead32", .address=0x3e9b },{ .name="MtrrGetAllMtrrs", .address=0x4509 },{ .name="MtrrLibSetMemoryType", .address=0x5d34 },{ .name="DebugPrint", .address=0x334a },{ .name="GetPowerOfTwo64", .address=0x3a10 },{ .name="GetSystemMemorySizeBelow4gb", .address=0x42dc },{ .name="MtrrSetMemoryAttributeInMtrrSettings.constprop.1", .address=0x1ab7 },{ .name="CpuDeadLoop", .address=0x32d6 },{ .name="MemEncryptSevIsEnabled", .address=0x31e1 },{ .name="QemuInitializeRam.lto_priv.35", .address=0x457c },{ .name="MtrrLibInitializeMtrrMask", .address=0x5f74 },{ .name="QemuFwCfgFindFile", .address=0x3eb7 },{ .name="PeiServicesInstallPpi", .address=0x3adc },{ .name="SaveAndDisableInterrupts", .address=0x32cb },{ .name="IoRead32", .address=0x3456 },{ .name="CopyGuid", .address=0x3c19 },{ .name="_ModuleEntryPoint", .address=0x240 },{ .name="BuildGuidDataHob", .address=0x3ce2 },{ .name="HighBitSet64", .address=0x39bc },{ .name="SetMem", .address=0x3db1 },{ .name="MtrrLibCalculateLeastMtrrs", .address=0x5af1 },{ .name="CopyMem.part.0", .address=0x3c57 },{ .name="GetPeiServicesTablePointer", .address=0x3a32 },{ .name="IoWrite32", .address=0x3419 },{ .name="MtrrLibPreMtrrChange", .address=0x607e },{ .name="PciCf8Or8", .address=0x35c7 },{ .name="DebugAssertEnabled", .address=0x3269 },{ .name="MtrrLibApplyVariableMtrrs", .address=0x48ca },{ .name="SetInterruptState", .address=0x32c0 },{ .name="AllocateZeroPool", .address=0x4074 },{ .name="IsMtrrSupported", .address=0x44bf },{ .name="AsciiSPrint.constprop.28", .address=0x6118 },{ .name="PciCf8Write32", .address=0x348d },{ .name="QemuFwCfgReadBytes", .address=0x3e7f },{ .name="BuildResourceDescriptorHob", .address=0x4019 },{ .name="LibPcdSet64S", .address=0x3bc1 }
        }
    }
};

#endif
