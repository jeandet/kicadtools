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
const char*    add_net_c  =  "(add_net";
const char*    angle_c  =  "(angle";
const char*    area_c  =  "(area";
const char*    arrow1a_c  =  "(arrow1a";
const char*    arrow1b_c  =  "(arrow1b";
const char*    arrow2a_c  =  "(arrow2a";
const char*    arrow2b_c  =  "(arrow2b";
const char*    at_c  =  "(at";
const char*    attr_c  =  "(attr";
const char*    center_c  =  "(center";
const char*    clearance_c  =  "(clearance";
const char*    code_c  =  "(code";
const char*    component_c  =  "(component";
const char*    components_c  =  "(components";
const char*    crossbar_c  =  "(crossbar";
const char*    date_c  =  "(date";
const char*    design_c  =  "(design";
const char*    dimension_c  =  "(dimension";
const char*    drawings_c  =  "(drawings";
const char*    drill_c  =  "(drill";
const char*    drillshape_c  =  "(drillshape";
const char*    edge_width_c  =  "(edge_width";
const char*    effects_c  =  "(effects";
const char*    end_c  =  "(end";
const char*    excludeedgelayer_c  =  "(excludeedgelayer";
const char*    export_c  =  "(export";
const char*    feature1_c  =  "(feature1";
const char*    feature2_c  =  "(feature2";
const char*    field_c  =  "(field";
const char*    fields_c  =  "(fields";
const char*    filled_polygon_c  =  "(filled_polygon";
const char*    font_c  =  "(font";
const char*    fp_circle_c  =  "(fp_circle";
const char*    fp_line_c  =  "(fp_line";
const char*    fp_text_c  =  "(fp_text";
const char*    general_c  =  "(general";
const char*    gr_arc_c  =  "(gr_arc";
const char*    gr_circle_c  =  "(gr_circle";
const char*    gr_line_c  =  "(gr_line";
const char*    gr_text_c  =  "(gr_text";
const char*    host_c  =  "(host";
const char*    hpglpendiameter_c  =  "(hpglpendiameter";
const char*    hpglpennumber_c  =  "(hpglpennumber";
const char*    hpglpenoverlay_c  =  "(hpglpenoverlay";
const char*    hpglpenspeed_c  =  "(hpglpenspeed";
const char*    kicad_pcb_c  =  "(kicad_pcb";
const char*    last_trace_width_c  =  "(last_trace_width";
const char*    layers_c  =  "(layers";
const char*    layer_c  =  "(layer";
const char*    layerselection_c  =  "(layerselection";
const char*    lib_c  =  "(lib";
const char*    libpart_c  =  "(libpart";
const char*    libparts_c  =  "(libparts";
const char*    libraries_c  =  "(libraries";
const char*    library_c  =  "(library";
const char*    libsource_c  =  "(libsource";
const char*    linewidth_c  =  "(linewidth";
const char*    links_c  =  "(links";
const char*    logical_c  =  "(logical";
const char*    mirror_c  =  "(mirror";
const char*    mod_edge_width_c  =  "(mod_edge_width";
const char*    mod_text_size_c  =  "(mod_text_size";
const char*    mode_c  =  "(mode";
const char*    model_c  =  "(model";
const char*    module_c  =  "(module";
const char*    modules_c  =  "(modules";
const char*    name_c  =  "(name";
const char*    names_c  =  "(names";
const char*    net_c  =  "(net";
const char*    net_class_c  =  "(net_class";
const char*    nets_c  =  "(nets";
const char*    no_connect_c  =  "(no_connect";
const char*    node_c  =  "(node";
const char*    num_c  =  "(num";
const char*    outputdirectory_c  =  "(outputdirectory";
const char*    outputformat_c  =  "(outputformat";
const char*    pad_c  =  "(pad";
const char*    pad_drill_c  =  "(pad_drill";
const char*    pad_size_c  =  "(pad_size";
const char*    pad_to_mask_clearance_c  =  "(pad_to_mask_clearance";
const char*    padsonsilk_c  =  "(padsonsilk";
const char*    page_c  =  "(page";
const char*    part_c  =  "(part";
const char*    path_c  =  "(path";
const char*    pcb_text_size_c  =  "(pcb_text_size";
const char*    pcb_text_width_c  =  "(pcb_text_width";
const char*    pcbplotparams_c  =  "(pcbplotparams";
const char*    pin_c  =  "(pin";
const char*    pins_c  =  "(pins";
const char*    plotframeref_c  =  "(plotframeref";
const char*    plotinvisibletext_c  =  "(plotinvisibletext";
const char*    plotothertext_c  =  "(plotothertext";
const char*    plotreference_c  =  "(plotreference";
const char*    plotvalue_c  =  "(plotvalue";
const char*    polygon_c  =  "(polygon";
const char*    psa4output_c  =  "(psa4output";
const char*    psnegative_c  =  "(psnegative";
const char*    pts_c  =  "(pts";
const char*    ref_c  =  "(ref";
const char*    rotate  =  "(rota";
const char*    scale_c  =  "(scale";
const char*    scaleselection_c  =  "(scaleselection";
const char*    segment_c  =  "(segment";
const char*    segment_width_c  =  "(segment_width";
const char*    setup_c  =  "(setup";
const char*    sheetpath_c  =  "(sheetpath";
const char*    size_c  =  "(size";
const char*    source_c  =  "(source";
const char*    start_c  =  "(start";
const char*    subtractmaskfromsilk_c  =  "(subtractmaskfromsilk";
const char*    tags_c  =  "(tags";
const char*    tedit_c  =  "(tedit";
const char*    thickness_c  =  "(thickness";
const char*    tool_c  =  "(tool";
const char*    trace_clearance_c  =  "(trace_clearance";
const char*    trace_min_c  =  "(trace_min";
const char*    trace_width_c  =  "(trace_width";
const char*    tracks_c  =  "(tracks";
const char*    tstamp_c  =  "(tstamp";
const char*    tstamps_c  =  "(tstamps";
const char*    type_c  =  "(type";
const char*    uri_c  =  "(uri";
const char*    useauxorigin_c  =  "(useauxorigin";
const char*    usegerberextensions_c  =  "(usegerberextensions";
const char*    uvia_dia_c  =  "(uvia_dia";
const char*    uvia_drill_c  =  "(uvia_drill";
const char*    uvia_min_drill_c  =  "(uvia_min_drill";
const char*    uvia_min_size_c  =  "(uvia_min_size";
const char*    uvia_size_c  =  "(uvia_size";
const char*    uvias_allowed_c  =  "(uvias_allowed";
const char*    value_c  =  "(value";
const char*    version_c  =  "(version";
const char*    via_c  =  "(via";
const char*    via_dia_c  =  "(via_dia";
const char*    via_drill_c  =  "(via_drill";
const char*    via_min_drill_c  =  "(via_min_drill";
const char*    via_min_size_c  =  "(via_min_size";
const char*    via_size_c  =  "(via_size";
const char*    viasonmask_c  =  "(viasonmask";
const char*    visible_elements_c  =  "(visible_elements";
const char*    width_c  =  "(width";
const char*    xyz  =  "(x";
const char*    xy_c  =  "(xy";
const char*    zone_45_only_c  =  "(zone_45_only";
const char*    zone_clearance_c  =  "(zone_clearance";
const char*    zone_c  =  "(zone";
const char*    zones_c  =  "(zones";



