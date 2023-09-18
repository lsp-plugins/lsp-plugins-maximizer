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

#include <lsp-plug.in/common/alloc.h>
#include <lsp-plug.in/common/debug.h>
#include <lsp-plug.in/dsp/dsp.h>
#include <lsp-plug.in/dsp-units/units.h>
#include <lsp-plug.in/plug-fw/meta/func.h>
#include <lsp-plug.in/stdlib/string.h>

#include <private/plugins/maximizer.h>

/* The size of temporary buffer for audio processing */
#define BUFFER_SIZE         0x1000U

namespace lsp
{
//    static plug::IPort *TRACE_PORT(plug::IPort *p)
//    {
//        lsp_trace("  port id=%s", (p)->metadata()->id);
//        return p;
//    }

    namespace plugins
    {
        //---------------------------------------------------------------------
        // Plugin factory
        static const meta::plugin_t *plugins[] =
        {
            &meta::maximizer_mono,
            &meta::maximizer_stereo
        };

        static plug::Module *plugin_factory(const meta::plugin_t *meta)
        {
            return new maximizer(meta);
        }

        static plug::Factory factory(plugin_factory, plugins, 2);

        //---------------------------------------------------------------------
        // Implementation
        maximizer::maximizer(const meta::plugin_t *meta):
            Module(meta)
        {
            nChannels   = 2;
            if (!strcmp(meta->uid, meta::maximizer_mono.uid))
                nChannels   = 1;

            vChannels   = NULL;

            pData       = NULL;
        }

        maximizer::~maximizer()
        {
            do_destroy();
        }

        void maximizer::init(plug::IWrapper *wrapper, plug::IPort **ports)
        {
            // Call parent class for initialization
            Module::init(wrapper, ports);

            size_t szof_channels    = align_size(sizeof(channel_t) * nChannels, DEFAULT_ALIGN);

            size_t to_alloc         = szof_channels;

            uint8_t *ptr            = alloc_aligned<uint8_t>(pData, to_alloc);
            if (ptr == NULL)
                return;

            // Allocate data
            vChannels               = reinterpret_cast<channel_t *>(ptr);
            ptr                    += szof_channels;

            for (size_t i=0; i<nChannels; ++i)
            {
                channel_t *c            = &vChannels[i];

                c->sBypass.construct();
                c->sOversampler.construct();

                c->vIn                  = NULL;
                c->vOut                 = NULL;
                c->vFftFreqs            = NULL;
                c->vWeighting           = NULL;

                for (size_t j=0; j<BAND_COUNT; ++j)
                {
                    band_t *b               = &c->vBands[j];

                    b->sInDelay.construct();
                    b->vBuffer              = NULL;
                    b->vWeighting           = NULL;
                }
                band_t              vBands[BAND_COUNT]; // Overall list of bands
            }

            // Bind ports
        }

        void maximizer::destroy()
        {
            Module::destroy();
            do_destroy();
        }

        void maximizer::do_destroy()
        {
        }

        void maximizer::update_sample_rate(long sr)
        {
        }

        void maximizer::update_settings()
        {
        }

        void maximizer::process(size_t samples)
        {
        }

        void maximizer::dump(dspu::IStateDumper *v) const
        {
            plug::Module::dump(v);
        }

    } /* namespace plugins */
} /* namespace lsp */


