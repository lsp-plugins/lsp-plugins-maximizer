/*
 * Copyright (C) 2023 Linux Studio Plugins Project <https://lsp-plug.in/>
 *           (C) 2023 Vladimir Sadovnikov <sadko4u@gmail.com>
 *
 * This file is part of lsp-plugins-maximizer
 * Created on: 18 сен 2023 г.
 *
 * lsp-plugins-maximizer is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * lsp-plugins-maximizer is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with lsp-plugins-maximizer. If not, see <https://www.gnu.org/licenses/>.
 */

#include <lsp-plug.in/plug-fw/meta/ports.h>
#include <lsp-plug.in/shared/meta/developers.h>
#include <private/meta/maximizer.h>

#define LSP_PLUGINS_MAXMIZER_VERSION_MAJOR       1
#define LSP_PLUGINS_MAXMIZER_VERSION_MINOR       0
#define LSP_PLUGINS_MAXMIZER_VERSION_MICRO       0

#define LSP_PLUGINS_MAXMIZER_VERSION  \
    LSP_MODULE_VERSION( \
        LSP_PLUGINS_MAXMIZER_VERSION_MAJOR, \
        LSP_PLUGINS_MAXMIZER_VERSION_MINOR, \
        LSP_PLUGINS_MAXMIZER_VERSION_MICRO  \
    )

namespace lsp
{
    namespace meta
    {
        //-------------------------------------------------------------------------
        // Plugin metadata
        static const port_item_t maximizer_tabs[] =
        {
            { "Level Control",      "maximizer.tabs.level_control"      },
            { NULL, NULL }
        };

    #define MAXIMIZER_COMMON \
        BYPASS

        // NOTE: Port identifiers should not be longer than 7 characters as it will overflow VST2 parameter name buffers
        static const port_t maximizer_mono_ports[] =
        {
            // Input and output audio ports
            PORTS_MONO_PLUGIN,
            MAXIMIZER_COMMON,

            PORTS_END
        };

        // NOTE: Port identifiers should not be longer than 7 characters as it will overflow VST2 parameter name buffers
        static const port_t maximizer_stereo_ports[] =
        {
            // Input and output audio ports
            PORTS_STEREO_PLUGIN,
            MAXIMIZER_COMMON,

            PORTS_END
        };

        static const int plugin_classes[]       = { C_LIMITER, -1 };
        static const int clap_features_mono[]   = { CF_AUDIO_EFFECT, CF_LIMITER, CF_MONO, -1 };
        static const int clap_features_stereo[] = { CF_AUDIO_EFFECT, CF_LIMITER, CF_STEREO, -1 };

        const meta::bundle_t maximizer_bundle =
        {
            "maximizer",
            "Maximizer",
            B_DYNAMICS,
            "", // TODO: provide ID of the video on YouTube
            "This plugins applies different techniques to make the sound as loud as possible while keeping it clean"
        };

        const plugin_t maximizer_mono =
        {
            "Maximizer Mono",
            "Maximizer Mono",
            "SM1M",
            &developers::v_sadovnikov,
            "maximizer_mono",
            LSP_LV2_URI("maximizer_mono"),
            LSP_LV2UI_URI("maximizer_mono"),
            "sm1m",
            LSP_LADSPA_MAXIMIZER_BASE + 0,
            LSP_LADSPA_URI("maximizer_mono"),
            LSP_CLAP_URI("maximizer_mono"),
            LSP_PLUGINS_MAXMIZER_VERSION,
            plugin_classes,
            clap_features_mono,
            E_DUMP_STATE,
            maximizer_mono_ports,
            "dynamics/maximizer/mono.xml",
            NULL,
            mono_plugin_port_groups,
            &maximizer_bundle
        };

        const plugin_t maximizer_stereo =
        {
            "Maximizer Stereo",
            "Maximizer Stereo",
            "SM1S",
            &developers::v_sadovnikov,
            "maximizer_stereo",
            LSP_LV2_URI("maximizer_stereo"),
            LSP_LV2UI_URI("maximizer_stereo"),
            "sm1s",
            LSP_LADSPA_MAXIMIZER_BASE + 1,
            LSP_LADSPA_URI("maximizer_stereo"),
            LSP_CLAP_URI("maximizer_stereo"),
            LSP_PLUGINS_MAXMIZER_VERSION,
            plugin_classes,
            clap_features_stereo,
            E_DUMP_STATE,
            maximizer_stereo_ports,
            "dynamics/maximizer/stereo.xml",
            NULL,
            stereo_plugin_port_groups,
            &maximizer_bundle
        };
    } /* namespace meta */
} /* namespace lsp */



