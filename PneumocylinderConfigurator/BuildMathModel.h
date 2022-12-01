#pragma once
#include <cassert>

#include <action_general.h>
#include <action_point.h>
#include <action_curve.h>
#include <action_curve3d.h>
#include <action_surface_curve.h>
#include <action_surface.h>
#include <action_direct.h>
#include <action_mesh.h>
#include <action_phantom.h>
#include <action_shell.h>
#include <action_sheet.h>
#include <action_solid.h>

#include <templ_s_array.h>
#include <templ_rp_array.h>
#include <templ_array2.h>
#include <templ_sptr.h>
#include <templ_dptr.h>

#include <mb_cart_point.h>
#include <mb_cart_point3d.h>
#include <mb_matrix.h>
#include <mb_matrix3d.h>
#include <mb_matrixnn.h>
#include <mb_placement.h>
#include <mb_placement3d.h>
#include <mb_axis3d.h>
#include <mb_thread.h>
#include <mb_nurbs_function.h>

#include <function.h>
#include <function_factory.h>

#include <curve.h>
#include <cur_line_segment.h>
#include <cur_arc.h>
#include <cur_nurbs.h>
#include <cur_hermit.h>
#include <cur_reparam_curve.h>
#include <cur_trimmed_curve.h>
#include <cur_character_curve.h>
#include <cur_polyline.h>
#include <cur_projection_curve.h>
#include <cur_contour.h>

#include <region.h>
#include <contour_graph.h>

#include <curve3d.h>
#include <cur_line_segment3d.h>
#include <cur_arc3d.h>
#include <cur_nurbs3d.h>
#include <cur_hermit3d.h>
#include <cur_trimmed_curve3d.h>
#include <cur_reparam_curve3d.h>
#include <cur_character_curve3d.h>
#include <cur_contour3d.h>
#include <cur_plane_curve.h>
#include <cur_surface_curve.h>
#include <cur_contour_on_surface.h>
#include <cur_silhouette_curve.h>
#include <cur_surface_intersection.h>
#include <cur_spiral.h>

#include <surface.h>
#include <surf_plane.h>
#include <surf_cylinder_surface.h>
#include <surf_cone_surface.h>
#include <surf_sphere_surface.h>
#include <surf_torus_surface.h>
#include <surf_extrusion_surface.h>
#include <surf_revolution_surface.h>
#include <surf_lofted_surface.h>
#include <surf_evolution_surface.h>
#include <surf_spiral_surface.h>
#include <surf_spline_surface.h>
#include <surf_offset_surface.h>
#include <surf_curve_bounded_surface.h>

#include <attribute_item.h>
#include <attr_color.h>
#include <attr_common_attribute.h>
#include <attr_dencity.h>
#include <attr_identifier.h>
#include <attr_selected.h>
#include <attr_user_attribute.h>
#include <attribute_container.h>

#include <name_item.h>
#include <name_check.h>

#include <topology.h>
#include <topology_faceset.h>
#include <check_geometry.h>

#include <point3d.h>
#include <point_frame.h>
#include <wire_frame.h>
#include <creator.h>
#include <cr_simple_creator.h>
#include <solid.h>
#include <instance_item.h>
#include <plane_instance.h>
#include <space_instance.h>
#include <assembly.h>

#include <mesh.h>
#include <mesh_grid.h>
#include <mesh_primitive.h>
#include <mesh_polygon.h>

#include <map_create.h>
#include <map_lump.h>
#include <map_section.h>
#include <map_section_complex.h>
#include <map_vestige.h>
#include <map_thread.h>

#include <tri_face.h>

#include <mip_curve_properties.h>
#include <mip_solid_area_volume.h>
#include <mip_solid_mass_inertia.h>

#include <cdet_bool.h>
#include <cdet_data.h>
#include <cdet_utility.h>
#include <part_solid.h>

#include <alg_base.h>
#include <alg_draw.h>
#include <generic_utility.h>
#include <conv_model_exchange.h>
#include <algorithm>
#include <ctime>
#include <functional>
#include <map>
#include <vector>
#include <utility>

#include <math_namespace.h>
#include <last.h>

//
//#include <test_samples.h>
//#include <test_manager.h>
#include <action_solid.h>
#include <creator.h>
#include <assembly.h>
#include <constraint.h>
#include <solid.h>
#include <instance_item.h>
#include <attr_common_attribute.h>
#include <templ_sptr.h>
#include <alg_draw.h>
#include <generic_utility.h>
#include <ctime>
#include <math_namespace.h>
#include <last.h>

#include <vector>
#include "alg_curve_fillet.h"
#include "mb_placement3d.h"
#include "cur_polyline.h"
#include "surf_plane.h"
#include "action_solid.h"
#include "cur_arc.h"
//Our Files
#include <math_namespace.h>

#include "colorDef.h"
#include "BuildParams.h"
//GCM
#include "gcm_api.h"
#include "gcm_constraint.h"
#include "gcm_manager.h"
#include "gcm_types.h"

using namespace c3d;
using namespace std;

namespace BuildMathModel {
	class ParametricModelCreator {
		static int colorScheme; // статическое поле инициализируется вне класса, в .cpp
		static int variantsConf;
	public:
		static MbModel* CreatePneymocylinderModel(BuildParams params);
	private:
		static MbAssembly* CreatePneumocylinderAssembly(BuildParams params);
	private:
		static void CreateBase(MbAssembly* pAsm, double ratio);
		//Переменные для поршня
		static SPtr<MbSolid> ParametricModelCreator::LIS_ME22_3_002_01_001();
		static SPtr<MbSolid> ParametricModelCreator::LIS_ME22_3_002_01_002();
		static SPtr<MbSolid> ParametricModelCreator::LIS_ME22_3_002_01_003();
		static SPtr<MbSolid> ParametricModelCreator::LIS_ME22_3_002_01_004(double length);
		static SPtr<MbSolid> ParametricModelCreator::LIS_ME22_3_002_01_005(double length);
		static SPtr<MbSolid> ParametricModelCreator::LIS_ME22_3_002_01_006();
		static SPtr<MbSolid> ParametricModelCreator::LIS_ME22_3_002_01_007();
		static SPtr<MbSolid> ParametricModelCreator::LIS_ME22_3_002_01_008();

		static SPtr<MbSolid> ParametricModelCreator::LIS_ME22_3_002_00_001();
		static SPtr<MbSolid> ParametricModelCreator::LIS_ME22_3_002_00_002();
		static SPtr<MbSolid> ParametricModelCreator::LIS_ME22_3_002_00_003();
		static SPtr<MbSolid> ParametricModelCreator::LIS_ME22_3_002_00_004();
		static SPtr<MbSolid> ParametricModelCreator::LIS_ME22_3_002_00_005();
		static SPtr<MbSolid> ParametricModelCreator::LIS_ME22_3_002_00_006();
		static SPtr<MbSolid> ParametricModelCreator::LIS_ME22_3_002_00_007();
		static SPtr<MbSolid> ParametricModelCreator::LIS_ME22_3_002_00_008();
		static SPtr<MbSolid> ParametricModelCreator::LIS_ME22_3_002_00_009();
		static SPtr<MbSolid> ParametricModelCreator::LIS_ME22_3_002_00_010();
		static SPtr<MbSolid> ParametricModelCreator::LIS_ME22_3_002_00_011();
		static SPtr<MbSolid> ParametricModelCreator::LIS_ME22_3_002_00_012();
		static SPtr<MbSolid> ParametricModelCreator::LIS_ME22_3_002_00_013();
		static SPtr<MbSolid> ParametricModelCreator::LIS_ME22_3_002_00_014();
		static SPtr<MbSolid> ParametricModelCreator::LIS_ME22_3_002_00_015();
		static SPtr<MbSolid> ParametricModelCreator::LIS_ME22_3_002_00_016();

		static SPtr<MbSolid> ParametricModelCreator::LIS_ME22_3_002_00_XXX();
		//Оси
		static SPtr<MbSolid> ParametricModelCreator::LIS_ME22_3_002_03_001();
		static SPtr<MbSolid> ParametricModelCreator::LIS_ME22_3_002_04_001();
		//переменные для Шатуна
		static SPtr<MbSolid> ParametricModelCreator::LIS_ME22_3_002_02_001(double length);
		static SPtr<MbSolid> ParametricModelCreator::LIS_ME22_3_002_02_002();
		static SPtr<MbSolid> ParametricModelCreator::LIS_ME22_3_002_02_003();
		static SPtr<MbSolid> ParametricModelCreator::LIS_ME22_3_002_02_004();

		static SPtr<MbSolid> ParametricModelCreator::GBolt4m10();
		static SPtr<MbSolid> ParametricModelCreator::GWasherA14();
		static SPtr<MbSolid> ParametricModelCreator::GWasherM20();
		static SPtr<MbSolid> ParametricModelCreator::GScrewM14();
		static SPtr<MbSolid> ParametricModelCreator::GScrewM10();
		static SPtr<MbSolid> ParametricModelCreator::GScrewM8();
	};
}
