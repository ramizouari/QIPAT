cmake_minimum_required(VERSION 3.22)
project(ImageProcessing)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_PREFIX_PATH /home/ramizouari/Qt/6.2.3/gcc_64/lib/cmake)
include_directories(.)
find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        Charts
        REQUIRED)

add_executable(ImageProcessing main.cpp image/Image.h image/reader.h image/reader.cpp image/Image.cpp image/stats.h image/stats.cpp image/filter/Filter.cpp image/filter/Filter.h image/Padding.cpp image/Padding.h gui/mainwindow.cpp gui/mainwindow.h gui/mainwindow.ui gui/histogram/Histogram.cpp gui/histogram/Histogram.h gui/histogram/histogram.ui gui/imageview.cpp gui/imageview.h gui/imageview.ui gui/histogram/HistogramCurveView.cpp gui/histogram/HistogramCurveView.h gui/statusbar/ImageInformationBar.cpp gui/statusbar/ImageInformationBar.h image/noise/ImpulsiveNoise.cpp image/noise/ImpulsiveNoise.h image/noise/Noise.cpp image/noise/Noise.h image/noise/GaussianNoise.cpp image/noise/GaussianNoise.h image/filter/MedianFilter.cpp image/filter/MedianFilter.h image/filter/ConvolutionalFilter.cpp image/filter/ConvolutionalFilter.h image/filter/MeanBlurFilter.cpp image/filter/MeanBlurFilter.h image/filter/edge/LaplacianFilter.cpp image/filter/edge/LaplacianFilter.h image/filter/IdentityFilter.cpp image/filter/IdentityFilter.h image/utils.h image/utils.cpp image/filter/edge/SobelFilter.cpp image/filter/edge/SobelFilter.h image/filter/gray/GrayFilter.cpp image/filter/gray/GrayFilter.h image/filter/gray/MaxChannelFilter.cpp image/filter/gray/MaxChannelFilter.h image/filter/gray/MeanChannelFilter.cpp image/filter/gray/MeanChannelFilter.h image/filter/edge/EdgeDetectionFilter.cpp image/filter/edge/EdgeDetectionFilter.h image/filter/differential/DifferentialFilter.cpp image/filter/differential/DifferentialFilter.h image/filter/differential/SobelOperator.cpp image/filter/differential/SobelOperator.h image/filter/gray/utils.cpp image/filter/gray/utils.h image/filter/differential/LaplacianOperator.cpp image/filter/differential/LaplacianOperator.h gui/options/PaddingInput.cpp gui/options/PaddingInput.h gui/options/GrayFilterInput.cpp gui/options/GrayFilterInput.h image/filter/gray/L1NormChannelFilter.cpp image/filter/gray/L1NormChannelFilter.h image/filter/gray/L2NormChannelFilter.cpp image/filter/gray/L2NormChannelFilter.h image/filter/differential/RobertsOperator.cpp image/filter/differential/RobertsOperator.h image/filter/edge/RobertsFilter.cpp image/filter/edge/RobertsFilter.h gui/options/FilterDialog.cpp gui/options/FilterDialog.h gui/histogram/HistogramCurve.cpp gui/histogram/HistogramCurve.h gui/options/ContrastDialog.cpp gui/options/ContrastDialog.h gui/options/ContrastTransformationView.cpp gui/options/ContrastTransformationView.h gui/options/ContrastForm.cpp gui/options/ContrastForm.h image/filter/global/IntensityFilter.cpp image/filter/global/IntensityFilter.h image/filter/global/HistogramEqualization.cpp image/filter/global/HistogramEqualization.h image/filter/global/GlobalFilter.cpp image/filter/global/GlobalFilter.h image/filter/global/IntensityMapper.cpp image/filter/global/IntensityMapper.h gui/options/MatrixInput.cpp gui/options/MatrixInput.h image/segmentation/OtsuSegmentation.cpp image/segmentation/OtsuSegmentation.h image/filter/spectral/SpectralFilter.cpp image/filter/spectral/SpectralFilter.h image/morphology/operators.cpp image/morphology/operators.h image/noise/SpeckleNoise.cpp image/noise/SpeckleNoise.h utility.h utility.cpp)
target_link_libraries(ImageProcessing
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Charts
        )

