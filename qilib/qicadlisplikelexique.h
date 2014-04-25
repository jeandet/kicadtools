/*------------------------------------------------------------------------------
--  This file is a part of the Kicad Tools Software
--  Copyright (C) 2014, Plasma Physics Laboratory - CNRS
--
--  This program is free software; you can redistribute it and/or modify
--  it under the terms of the GNU General Public License as published by
--  the Free Software Foundation; either version 2 of the License, or
--  (at your option) any later version.
--
--  This program is distributed in the hope that it will be useful,
--  but WITHOUT ANY WARRANTY; without even the implied warranty of
--  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
--  GNU General Public License for more details.
--
--  You should have received a copy of the GNU General Public License
--  along with this program; if not, write to the Free Software
--  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
-------------------------------------------------------------------------------*/
/*--                  Author : Alexis Jeandet
--                     Mail : alexis.jeandet@member.fsf.org
----------------------------------------------------------------------------*/
/*
 *          Have a look to LispLikeLexique.ods
*/
#ifndef LEXIQUE_H
#define LEXIQUE_H

namespace QIlib{

namespace Lexique
{
extern "C" const char*   add_net_c;
extern "C" const char*   area_c;
extern "C" const char*   at_c;
extern "C" const char*   attr_c;
extern "C" const char*   center_c;
extern "C" const char*   clearance_c;
extern "C" const char*   code_c;
extern "C" const char*   component_c;
extern "C" const char*   components_c;
extern "C" const char*   date_c;
extern "C" const char*   design_c;
extern "C" const char*   drawings_c;
extern "C" const char*   drillshape_c;
extern "C" const char*   edge_width_c;
extern "C" const char*   effects_c;
extern "C" const char*   end_c;
extern "C" const char*   excludeedgelayer_c;
extern "C" const char*   export_c;
extern "C" const char*   field_c;
extern "C" const char*   fields_c;
extern "C" const char*   font_c;
extern "C" const char*   fp_circle_c;
extern "C" const char*   fp_line_c;
extern "C" const char*   fp_text_c;
extern "C" const char*   general_c;
extern "C" const char*   host_c;
extern "C" const char*   hpglpendiameter_c;
extern "C" const char*   hpglpennumber_c;
extern "C" const char*   hpglpenoverlay_c;
extern "C" const char*   hpglpenspeed_c;
extern "C" const char*   last_trace_width_c;
extern "C" const char*   layers_c;
extern "C" const char*   layerselection_c;
extern "C" const char*   lib_c;
extern "C" const char*   libpart_c;
extern "C" const char*   libparts_c;
extern "C" const char*   libraries_c;
extern "C" const char*   library_c;
extern "C" const char*   libsource_c;
extern "C" const char*   linewidth_c;
extern "C" const char*   links_c;
extern "C" const char*   logical_c;
extern "C" const char*   mirror_c;
extern "C" const char*   mod_edge_width_c;
extern "C" const char*   mod_text_size_c;
extern "C" const char*   mode_c;
extern "C" const char*   model_c;
extern "C" const char*   module_c;
extern "C" const char*   modules_c;
extern "C" const char*   name_c;
extern "C" const char*   names_c;
extern "C" const char*   net_c;
extern "C" const char*   net_class_c;
extern "C" const char*   nets_c;
extern "C" const char*   no_connect_c;
extern "C" const char*   node_c;
extern "C" const char*   num_c;
extern "C" const char*   outputdirectory_c;
extern "C" const char*   outputformat_c;
extern "C" const char*   pad_c;
extern "C" const char*   pad_drill_c;
extern "C" const char*   pad_size_c;
extern "C" const char*   pad_to_mask_clearance_c;
extern "C" const char*   padsonsilk_c;
extern "C" const char*   page_c;
extern "C" const char*   part_c;
extern "C" const char*   path_c;
extern "C" const char*   pcb_text_size_c;
extern "C" const char*   pcb_text_width_c;
extern "C" const char*   pcbplotparams_c;
extern "C" const char*   pin_c;
extern "C" const char*   pins_c;
extern "C" const char*   plotframeref_c;
extern "C" const char*   plotinvisibletext_c;
extern "C" const char*   plotothertext_c;
extern "C" const char*   plotreference_c;
extern "C" const char*   plotvalue_c;
extern "C" const char*   psa4output_c;
extern "C" const char*   psnegative_c;
extern "C" const char*   ref_c;
extern "C" const char*   rotate;
extern "C" const char*   scale_c;
extern "C" const char*   scaleselection_c;
extern "C" const char*   segment_width_c;
extern "C" const char*   setup_c;
extern "C" const char*   sheetpath_c;
extern "C" const char*   source_c;
extern "C" const char*   start_c;
extern "C" const char*   subtractmaskfromsilk_c;
extern "C" const char*   tags_c;
extern "C" const char*   tedit_c;
extern "C" const char*   thickness_c;
extern "C" const char*   tool_c;
extern "C" const char*   trace_clearance_c;
extern "C" const char*   trace_min_c;
extern "C" const char*   trace_width_c;
extern "C" const char*   tracks_c;
extern "C" const char*   tstamp_c;
extern "C" const char*   tstamps_c;
extern "C" const char*   type_c;
extern "C" const char*   uri_c;
extern "C" const char*   useauxorigin_c;
extern "C" const char*   usegerberextensions_c;
extern "C" const char*   uvia_dia_c;
extern "C" const char*   uvia_drill_c;
extern "C" const char*   uvia_min_drill_c;
extern "C" const char*   uvia_min_size_c;
extern "C" const char*   uvia_size_c;
extern "C" const char*   uvias_allowed_c;
extern "C" const char*   value_c;
extern "C" const char*   version_c;
extern "C" const char*   via_dia_c;
extern "C" const char*   via_drill_c;
extern "C" const char*   via_min_drill_c;
extern "C" const char*   via_min_size_c;
extern "C" const char*   via_size_c;
extern "C" const char*   viasonmask_c;
extern "C" const char*   visible_elements_c;
extern "C" const char*   width_c;
extern "C" const char*   xyz;
extern "C" const char*   zone_45_only_c;
extern "C" const char*   zone_clearance_c;
extern "C" const char*   zones_c;
}
}

#endif // LEXIQUE_H
