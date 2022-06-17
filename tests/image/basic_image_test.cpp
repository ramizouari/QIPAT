//
// Created by ramizouari on 30/05/22.
//
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE IMAGE_TEST
#include <boost/test/unit_test.hpp>
#include <boost/mpl/list.hpp>
#include <boost/mp11/list.hpp>
#include "image/Image.h"
#include "image/ImageReader.h"
#include <filesystem>
#include <fstream>

using namespace image;

BOOST_AUTO_TEST_SUITE(basic_image)
    BOOST_AUTO_TEST_SUITE(construction)
        BOOST_AUTO_TEST_CASE(grey_image)
        {
            BOOST_TEST_MESSAGE("Testing grey image construction");
            Image I({{1,2,3},{4,5,6}});
            BOOST_REQUIRE_EQUAL(I.width,2);
            BOOST_REQUIRE_EQUAL(I.height,3);
            BOOST_REQUIRE_EQUAL(I.nb_channel,1);
            BOOST_CHECK_EQUAL(I(0,0),1);
            BOOST_CHECK_EQUAL(I(0,1),2);
            BOOST_CHECK_EQUAL(I(0,2),3);
            BOOST_CHECK_EQUAL(I(1,0),4);
            BOOST_CHECK_EQUAL(I(1,1),5);
            BOOST_CHECK_EQUAL(I(1,2),6);
        }

        BOOST_AUTO_TEST_CASE(rgb_image)
        {
            BOOST_TEST_MESSAGE("Testing grey image construction");
            Image I({{{1,2,3},{4,5,6}},{{7,8,9},{10,11,12}},{{13,14,15},{16,17,18}}});
            BOOST_REQUIRE_EQUAL(I.width,2);
            BOOST_REQUIRE_EQUAL(I.height,3);
            BOOST_REQUIRE_EQUAL(I.nb_channel,3);
            for(int c=0;c<3;c++) for(int i=0;i<2;i++) for(int j=0;j<3;j++)
                BOOST_CHECK_EQUAL(I(c,i,j),c*6+i*3+j+1);

        }

    BOOST_AUTO_TEST_SUITE_END()
    BOOST_AUTO_TEST_SUITE(assign)
        BOOST_AUTO_TEST_CASE(grey_image)
        {
            BOOST_TEST_MESSAGE("Testing grey image assignment");
            Image I({{1,2,3},{4,5,6}});
            I(0,2)=15;
            BOOST_REQUIRE_EQUAL(I.width,2);
            BOOST_REQUIRE_EQUAL(I.height,3);
            BOOST_REQUIRE_EQUAL(I.nb_channel,1);
            BOOST_CHECK_EQUAL(I(0,0),1);
            BOOST_CHECK_EQUAL(I(0,1),2);
            BOOST_CHECK_EQUAL(I(0,2),15);
            BOOST_CHECK_EQUAL(I(1,0),4);
            BOOST_CHECK_EQUAL(I(1,1),5);
            BOOST_CHECK_EQUAL(I(1,2),6);
        }

        BOOST_AUTO_TEST_CASE(rgb_image)
        {
            BOOST_TEST_MESSAGE("Testing rgb image construction");
            Image I({{{1,2,3},{4,5,6}},{{7,8,9},{10,11,12}},{{13,14,15},{16,17,18}}});
            I(0,1,1)=15;
            BOOST_REQUIRE_EQUAL(I.width,2);
            BOOST_REQUIRE_EQUAL(I.height,3);
            BOOST_REQUIRE_EQUAL(I.nb_channel,3);
            for(int c=0;c<3;c++) for(int i=0;i<2;i++) for(int j=0;j<3;j++)
                        BOOST_CHECK_EQUAL(I(c,i,j), c==0 && i==1 && j==1?15:c*6+i*3+j+1);

        }
    BOOST_AUTO_TEST_SUITE_END()

    BOOST_AUTO_TEST_SUITE(read_image)
        BOOST_AUTO_TEST_CASE(pbm_ascii)
        {
            BOOST_TEST_MESSAGE("Testing pbm ascii image reading");
            auto tmpPath=std::filesystem::temp_directory_path()/"P1Test";
            std::ofstream file(tmpPath);
            file << R"(P1
# comment
# This is a test File
2 3
0 1 1
0 0 0)" << std::flush;
            file.close();
            PNMReader reader;
            auto image=reader.read(tmpPath.string());
            BOOST_CHECK_EQUAL(image.width,3);
            BOOST_CHECK_EQUAL(image.height,2);
            BOOST_CHECK_EQUAL(image.nb_channel,1);
            BOOST_CHECK_EQUAL(image.max,1);
            for(int i=0;i<3;i++) for(int j=0;j<2;j++)
                BOOST_CHECK_EQUAL(image(i,j),i+j!=1);
        }


        BOOST_AUTO_TEST_CASE(pgm_ascii)
        {
            BOOST_TEST_MESSAGE("Testing pgm ascii image reading");
            auto tmpPath=std::filesystem::temp_directory_path()/"P2Test";
            std::ofstream file(tmpPath);
            file << R"(P2
# comment
# This is a test File
# size of image
2 3
# number of gray levels
258
1 7 99
6 88 257)" << std::flush;
            file.close();
            PNMReader reader;
            auto image=reader.read(tmpPath.string());
            BOOST_REQUIRE_EQUAL(image.width,3);
            BOOST_REQUIRE_EQUAL(image.height,2);
            BOOST_REQUIRE_EQUAL(image.nb_channel,1);
            BOOST_REQUIRE_EQUAL(image.max,258);
            std::vector<std::vector<int>> data({{1,7},{99,6},{88,257}});
            for(int i=0;i<3;i++) for(int j=0;j<2;j++)
                    BOOST_CHECK_EQUAL(image(i,j),data[i][j]);
        }

        BOOST_AUTO_TEST_CASE(pgm_binary)
        {
            BOOST_TEST_MESSAGE("Testing pgm binary image reading");
            auto tmpPath=std::filesystem::temp_directory_path()/"P5Test";
            std::ofstream file(tmpPath);
            file << R"(P5
# comment
# This is a test File
# size of image
2 3
# number of gray levels
195)" << std::endl;
            auto formula=[](auto i,auto j){return (i+57)+(j+89)%195;};
            for(int i=0;i<3;i++) for(int j=0;j<2;j++)
                    file.put(formula(i,j));
            file.close();
            PNMReader reader;
            auto image=reader.read(tmpPath.string());
            BOOST_REQUIRE_EQUAL(image.width,3);
            BOOST_REQUIRE_EQUAL(image.height,2);
            BOOST_REQUIRE_EQUAL(image.nb_channel,1);
            for(int i=0;i<3;i++) for(int j=0;j<2;j++)
                BOOST_CHECK_EQUAL(image(i,j),formula(i,j));
        }

        BOOST_AUTO_TEST_CASE(pbm_binary)
        {
            BOOST_TEST_MESSAGE("Testing pbm binary image reading");
            auto tmpPath=std::filesystem::temp_directory_path()/"P4Test";
            std::ofstream file(tmpPath);
            file << R"(P4
# comment
# This is a test File
# size of image
2 3)" << std::endl;
            for(int i=0;i<3;i++) for(int j=0;j<2;j++)
                    file.put(i+j==1);
            file.close();
            PNMReader reader;
            auto image=reader.read(tmpPath.string());
            BOOST_REQUIRE_EQUAL(image.width,3);
            BOOST_REQUIRE_EQUAL(image.height,2);
            BOOST_REQUIRE_EQUAL(image.nb_channel,1);
            BOOST_REQUIRE_EQUAL(image.max,1);
            for(int i=0;i<3;i++) for(int j=0;j<2;j++)
                    BOOST_CHECK_EQUAL(image(i,j),i+j!=1);
        }


    BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()