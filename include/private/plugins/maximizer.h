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

#ifndef PRIVATE_PLUGINS_MAXIMIZER_H_
#define PRIVATE_PLUGINS_MAXIMIZER_H_

#include <lsp-plug.in/dsp-units/ctl/Bypass.h>
#include <lsp-plug.in/dsp-units/util/Delay.h>
#include <lsp-plug.in/dsp-units/util/Oversampler.h>
#include <lsp-plug.in/dsp-units/util/SpectralSplitter.h>
#include <lsp-plug.in/plug-fw/plug.h>
#include <private/meta/maximizer.h>

namespace lsp
{
    namespace plugins
    {
        /**
         * Base class for the latency compensation delay
         */
        class maximizer: public plug::Module
        {
            private:
                maximizer & operator = (const maximizer &);
                maximizer (const maximizer &);

            protected:
                enum band_type_t
                {
                    BAND_K_FULL,
                    BAND_LOW,
                    BAND_K_LOW,
                    BAND_MID,
                    BAND_K_MID,
                    BAND_HIGH,
                    BAND_K_HIGH,

                    BAND_COUNT
                };

                typedef struct band_t
                {
                    dspu::Delay             sInDelay;           // Delay compensation for input level adjustment
                    float                  *vBuffer;            // Processing buffer
                    float                  *vWeighting;         // Weighting and crossover functions combined
                } band_t;

                typedef struct channel_t
                {
                    dspu::Bypass            sBypass;            // Bypass
                    dspu::Oversampler       sOversampler;       // Oversampler
                    dspu::SpectralSplitter  sSplitter;          // Spectral splitter

                    float                  *vIn;                // Input buffer
                    float                  *vOut;               // Output buffer
                    float                  *vFftFreqs;          // List of FFT frequencies
                    float                  *vWeighting;         // Weighted magnitude

                    band_t                  vBands[BAND_COUNT]; // Overall list of bands
                } channel_t;

            protected:
                size_t                  nChannels;          // Number of channels
                channel_t              *vChannels;          // Channel data

                uint8_t                *pData;              // Allocated data

            protected:
                void                    do_destroy();

            public:
                explicit maximizer(const meta::plugin_t *meta);
                virtual ~maximizer() override;

                virtual void            init(plug::IWrapper *wrapper, plug::IPort **ports) override;
                virtual void            destroy() override;

            public:
                virtual void            update_sample_rate(long sr) override;
                virtual void            update_settings() override;
                virtual void            process(size_t samples) override;
                virtual void            dump(dspu::IStateDumper *v) const override;
        };

    } /* namespace plugins */
} /* namespace lsp */


#endif /* PRIVATE_PLUGINS_MAXIMIZER_H_ */

