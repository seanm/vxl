#include <testlib/testlib_test.h>
#include <volm/volm_category_io.h>


static void write_osm_samples()
{
  // input file sample
  // transformation from open_street_map to 
  vcl_string osm_land_file = "./osm_to_volm_land.txt";
  vcl_ofstream ofs_land(osm_land_file.c_str());
  // header
  ofs_land << "Key Value id name level\n";
  // contents
  ofs_land << "landuse reservoir 1 Open_Water 0\n";
  ofs_land << "landuse greenhouse_horticulture 13 Cultivated_Crops 0\n";
  ofs_land << "man_made monitoring_station 15 building 4\n";
  ofs_land << "emergency ambulance_station 48 hostptial 2\n";
  ofs_land << "tourism viewpoint 141 tourism_viewpoint 4\n";
  ofs_land.close();

  // road width file
  vcl_string road_width_file = "./osm_road_width.txt";
  vcl_ofstream ofs_road(road_width_file.c_str());
  // header
  ofs_road << "Key Value Width(0 means the categroy is not a road)\n";
  // contents
  ofs_road << "abutters commercial 1.00\n";
  ofs_road << "amenity kindergarten 0.00\n";
  ofs_road << "barrier city_wall 12.00\n";
  ofs_road << "highway living_street 2.50\n";
  ofs_road.close();
}

static void test_category_io_read_land_category(vcl_string filename)
{
  vcl_map<vcl_pair<vcl_string, vcl_string>, volm_land_layer> osm_land_table;
  TEST("land_category_io", volm_osm_category_io::load_category_table(filename, osm_land_table), true);
  vcl_map<vcl_pair<vcl_string, vcl_string>, volm_land_layer>::iterator mit = osm_land_table.begin();
  for (; mit != osm_land_table.end(); ++mit)
    vcl_cout << " tag = " << mit->first.first << ", value = " << mit->first.second << ", ---> id = "
             << (int)(osm_land_table[vcl_pair<vcl_string,vcl_string>(mit->first.first, mit->first.second)].id_) << ", "
             << osm_land_table[vcl_pair<vcl_string,vcl_string>(mit->first.first, mit->first.second)].name_ << ", "
             << (int)(osm_land_table[vcl_pair<vcl_string,vcl_string>(mit->first.first, mit->first.second)].level_) << vcl_endl;
}

static void test_category_io_load_road_width(vcl_string const& filename)
{
  vcl_map<vcl_pair<vcl_string, vcl_string>, float> volm_road_width;
  TEST("road_width_io", volm_osm_category_io::load_road_width_table(filename, volm_road_width), true);
  vcl_map<vcl_pair<vcl_string, vcl_string>, float>::iterator mit = volm_road_width.begin();
  for (; mit != volm_road_width.end(); ++mit)
    vcl_cout << " tag = " << mit->first.first << ", value = " << mit->first.second << " ---> width = "
             << volm_road_width[vcl_pair<vcl_string, vcl_string>(mit->first.first, mit->first.second)] << vcl_endl;
}

static void test_category_io()
{
  // create sample files
  write_osm_samples();

  // test the method of loading land category
  vcl_string osm_to_volm_file = "./osm_to_volm_land.txt";
  test_category_io_read_land_category(osm_to_volm_file);

  // test the method of loading road width
  vcl_string road_width_file = "./osm_road_width.txt";
 
  test_category_io_load_road_width(road_width_file);
}

TESTMAIN(test_category_io);