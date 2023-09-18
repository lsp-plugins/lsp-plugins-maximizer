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

#ifndef PRIVATE_META_MAXIMIZER_H_
#define PRIVATE_META_MAXIMIZER_H_

#include <lsp-plug.in/plug-fw/meta/types.h>
#include <lsp-plug.in/plug-fw/const.h>

namespace lsp
{
    //-------------------------------------------------------------------------
    // Plugin metadata
    namespace meta
    {
        typedef struct maximizer
        {
        } maximizer;

        // Plugin type metadata
        extern const plugin_t maximizer_mono;
        extern const plugin_t maximizer_stereo;

    } /* namespace meta */
} /* namespace lsp */

#endif /* PRIVATE_META_MAXIMIZER_H_ */
