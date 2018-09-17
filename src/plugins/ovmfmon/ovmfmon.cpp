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

#include <glib.h>
#include <config.h>
#include <inttypes.h>
#include <libvmi/libvmi.h>
#include <assert.h>

#include "../plugins.h"
#include "ovmfmon.h"
#include "private.h"

event_response_t trap_cb(drakvuf_t drakvuf, drakvuf_trap_info_t* info)
{
    printf("%s 0x%lx\n", info->trap->breakpoint.module, info->trap_pa);
    return 0;
}

static bool find_ovmf_base(drakvuf_t drakvuf, ovmfmon* o)
{
    vmi_instance_t vmi = drakvuf_lock_and_get_vmi(drakvuf);
    addr_t search = OVMF_END - ((PAGE_SIZE + OVMF_MAXOFFSET) & ~OVMF_MAXOFFSET);
    EFI_FIRMWARE_VOLUME_HEADER fvh = {{ 0 }};
    addr_t ovmf_base = 0, max_addr = vmi_get_max_physical_address(vmi);

    printf("Max addr: 0x%lx. Search start: 0x%lx\n", max_addr, search);

    while (max_addr <= search && search > LOWCHUNK_BEGIN + LOWCHUNK_SIZE)
    {
        if ( VMI_FAILURE == vmi_read_pa(vmi, search, sizeof(EFI_FIRMWARE_VOLUME_HEADER), &fvh, NULL) )
        {
            printf("Failed to read page 0x%lx in search for fvh\n", search);
            break;
        }

        if ( fvh.Signature == EFI_FVH_SIGNATURE )
        {
            ovmf_base = search;
        }

        search -= PAGE_SIZE;
    }

    drakvuf_release_vmi(drakvuf);

    if ( !ovmf_base )
        return 0;

    printf("OVMF Base load address: 0x%lx\n", ovmf_base);

    return 1;
}

bool trap_modules(drakvuf_t drakvuf, ovmfmon *o)
{
    unsigned int i;
    for (i=0;i<1;i++) {
        printf("Trapping functions of %s\n", modules[i].name);
        unsigned int z;
        for(z=0;z<modules[i].fcount;z++) {

            if (strcmp(modules[i].function[z].name, "SecCoreStartupWithStack"))
                continue;

            printf("%s.%s @ 0x%lx\n",
                    modules[i].name, modules[i].function[z].name, modules[i].BaseAddress + modules[i].function[z].address);

            drakvuf_trap_t *trap = (drakvuf_trap_t*)g_malloc0(sizeof(drakvuf_trap_t));
            if ( !trap )
                return false;

            trap->breakpoint.addr_type = ADDR_PA;
            trap->breakpoint.module = modules[i].name;
            trap->breakpoint.addr = modules[i].BaseAddress + modules[i].function[z].address;
            trap->type = BREAKPOINT;
            trap->data = (void*)drakvuf;
            trap->cb = trap_cb;

            drakvuf_add_trap(drakvuf, trap);
            o->traps = g_slist_prepend(o->traps, trap);
        }
    }

    return 1;
}

/* Checksum with the sum over bytes 0..length == 0 */
static inline bool verify_ovmf_info_checksum(struct ovmf_info *ovmf_info)
{
    uint8_t checksum = 0, i;
    for ( i = 0; i < ovmf_info->length; i++ )
        checksum += ((uint8_t *)(ovmf_info))[i];

    return checksum ? false : true;
}

event_response_t startup_cb(drakvuf_t drakvuf, drakvuf_trap_info_t* info)
{
    printf("SecCoreStartupWithStack cb!\n");
    drakvuf_remove_trap(drakvuf, info->trap, NULL);
    return 0;
}

event_response_t info_page_cb(drakvuf_t drakvuf, drakvuf_trap_info_t* info)
{
    vmi_instance_t vmi = drakvuf_lock_and_get_vmi(drakvuf);
    struct ovmf_info ovmf_info = {{ 0 }};
    vmi_read_pa(vmi, OVMF_INFO_PHYSICAL_ADDRESS, sizeof(struct ovmf_info), &ovmf_info, NULL);
    drakvuf_release_vmi(drakvuf);

    if ( strncmp("XenHVMOVMF", ovmf_info.signature, 10) )
        return 0;

    if ( !verify_ovmf_info_checksum(&ovmf_info) )
        return 0;

    PRINT_DEBUG("Xen hvmloader finished loading OVMF\n");

    drakvuf_remove_trap(drakvuf, info->trap, NULL);

    ovmfmon *o = (ovmfmon*)info->trap->data;

    o->page[1].cb = startup_cb;
    o->page[1].data = info->trap->data;
    o->page[1].type = MEMACCESS;
    o->page[1].memaccess.type = POST;
    o->page[1].memaccess.access = VMI_MEMACCESS_X;

    unsigned int z;
    for(z=0;z<modules[0].fcount;z++)
    {
        if (strcmp(modules[0].function[z].name, "SecCoreStartupWithStack"))
            continue;

        addr_t addr = modules[0].BaseAddress + modules[0].function[z].address;
        printf("%s.SecCoreStartupWithStack @ 0x%lx\n", modules[0].name, addr);

        o->page[1].memaccess.gfn = addr >> 12;
    }

    if ( o->page[1].memaccess.gfn && drakvuf_add_trap(drakvuf, &o->page[1]) )
    {
        printf("Added gfn watch on SecCoreStartupWithStack\n");
    }

    return 0;
}

ovmfmon::ovmfmon(drakvuf_t drakvuf, const void* config, output_format_t output)
{
    this->format = output;

    vmi_instance_t vmi = drakvuf_lock_and_get_vmi(drakvuf);
    struct ovmf_info ovmf_info = {{ 0 }};
    vmi_read_pa(vmi, OVMF_INFO_PHYSICAL_ADDRESS, sizeof(struct ovmf_info), &ovmf_info, NULL);
    drakvuf_release_vmi(drakvuf);

    if ( strncmp("XenHVMOVMF", ovmf_info.signature, 10) || !verify_ovmf_info_checksum(&ovmf_info) )
    {
        PRINT_DEBUG("No OVMF signature found on info page, wait for hvmloader to finish\n");
        this->page[0].cb = info_page_cb;
        this->page[0].data = (void*)this;
        this->page[0].type = MEMACCESS;
        this->page[0].memaccess.gfn = OVMF_INFO_PHYSICAL_ADDRESS >> 12;
        this->page[0].memaccess.type = POST;
        this->page[0].memaccess.access = VMI_MEMACCESS_W;

        if ( !drakvuf_add_trap(drakvuf, &this->page[0]) )
            throw -1;
    } else {
        find_ovmf_base(drakvuf, this);
        trap_modules(drakvuf, this);
    }
}

ovmfmon::~ovmfmon(void) {}
