cmake_minimum_required(VERSION 3.22)
project(ImageProcessing)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
include_directories(.)
find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        Charts
        DataVisualization
        REQUIRED)

find_package(muparser REQUIRED)


set(UTILITY_SOURCES
        utility.h utility.cpp)

set(CORE_SOURCES
        main.cpp
        image/Image.h image/Image.cpp
        image/ImageReader.h image/ImageReader.cpp
        image/stats.h image/stats.cpp
        image/filter/Filter.cpp image/filter/Filter.h
        image/Padding.cpp image/Padding.h
        image/noise/ImpulsiveNoise.cpp image/noise/ImpulsiveNoise.h
        image/noise/Noise.cpp image/noise/Noise.h
        image/noise/GaussianNoise.cpp image/noise/GaussianNoise.h
        image/filter/MedianFilter.cpp image/filter/MedianFilter.h
        image/filter/ConvolutionalFilter.cpp image/filter/ConvolutionalFilter.h
        image/filter/MeanBlurFilter.cpp image/filter/MeanBlurFilter.h
        image/filter/edge/LaplacianFilter.cpp image/filter/edge/LaplacianFilter.h
        image/filter/IdentityFilter.cpp image/filter/IdentityFilter.h
        image/utils.h image/utils.cpp
        image/filter/edge/SobelFilter.cpp image/filter/edge/SobelFilter.h
        image/filter/gray/GrayFilter.cpp image/filter/gray/GrayFilter.h
        image/filter/gray/MaxChannelFilter.cpp image/filter/gray/MaxChannelFilter.h
        image/filter/gray/MeanChannelFilter.cpp image/filter/gray/MeanChannelFilter.h
        image/filter/edge/EdgeDetectionFilter.cpp image/filter/edge/EdgeDetectionFilter.h
        image/filter/differential/DifferentialFilter.cpp image/filter/differential/DifferentialFilter.h
        image/filter/differential/SobelOperator.cpp image/filter/differential/SobelOperator.h
        image/filter/gray/utils.cpp image/filter/gray/utils.h
        image/filter/differential/LaplacianOperator.cpp image/filter/differential/LaplacianOperator.h
        image/filter/gray/L1NormChannelFilter.cpp image/filter/gray/L1NormChannelFilter.h
        image/filter/gray/L2NormChannelFilter.cpp image/filter/gray/L2NormChannelFilter.h
        image/filter/differential/RobertsOperator.cpp image/filter/differential/RobertsOperator.h
        image/filter/edge/RobertsFilter.cpp image/filter/edge/RobertsFilter.h
        image/filter/global/IntensityFilter.cpp image/filter/global/IntensityFilter.h
        image/filter/global/HistogramEqualization.cpp image/filter/global/HistogramEqualization.h
        image/filter/global/GlobalFilter.cpp image/filter/global/GlobalFilter.h
        image/filter/global/IntensityMapper.cpp image/filter/global/IntensityMapper.h
        image/segmentation/OtsuSegmentation.cpp image/segmentation/OtsuSegmentation.h
        image/filter/spectral/SpectralFilter.cpp image/filter/spectral/SpectralFilter.h
        image/morphology/operators.cpp image/morphology/operators.h
        image/noise/SpeckleNoise.cpp image/noise/SpeckleNoise.h
        image/filter/GaussianBlurFilter.cpp image/filter/GaussianBlurFilter.h
        image/segmentation/ThresholdSegmentation.cpp image/segmentation/ThresholdSegmentation.h
        image/Operator.cpp image/Operator.h
        image/segmentation/Segmentation.cpp image/segmentation/Segmentation.h
        image/Mask.cpp image/Mask.h
        image/ImageWriter.h image/ImageWriter.cpp
        image/ImageFormat.h
        )
set(GUI_SOURCES
        gui/mainwindow.cpp gui/mainwindow.h gui/mainwindow.ui
        gui/histogram/Histogram.cpp gui/histogram/Histogram.h gui/histogram/histogram.ui
        gui/imageview.cpp gui/imageview.h gui/imageview.ui
        gui/histogram/HistogramCurveView.cpp gui/histogram/HistogramCurveView.h
        gui/statusbar/ImageInformationBar.cpp gui/statusbar/ImageInformationBar.h
        gui/options/PaddingInput.cpp gui/options/PaddingInput.h
        gui/options/GrayFilterInput.cpp gui/options/GrayFilterInput.h
        gui/options/FilterDialog.cpp gui/options/FilterDialog.h
        gui/histogram/HistogramCurve.cpp gui/histogram/HistogramCurve.h
        gui/options/ContrastDialog.cpp gui/options/ContrastDialog.h
        gui/options/ContrastTransformationView.cpp gui/options/ContrastTransformationView.h
        gui/options/ContrastForm.cpp gui/options/ContrastForm.h
        gui/options/SpectrumMaskDialog.cpp gui/options/SpectrumMaskDialog.h
        gui/spectrum/mask/RectangleMaskForm.cpp gui/spectrum/mask/RectangleMaskForm.h
        gui/spectrum/mask/MaskForm.cpp gui/spectrum/mask/MaskForm.h
        gui/spectrum/mask/CircleMaskForm.cpp gui/spectrum/mask/CircleMaskForm.h
        gui/spectrum/mask/RelationalEquationMaskForm.cpp gui/spectrum/mask/RelationalEquationMaskForm.h
        gui/spectrum/filter/FilterForm.cpp gui/spectrum/filter/FilterForm.h
        gui/options/SpectrumFilterDialog.cpp gui/options/SpectrumFilterDialog.h
        gui/spectrum/filter/GaussianBlurForm.cpp gui/spectrum/filter/GaussianBlurForm.h
        gui/spectrum/filter/MeanBlurForm.cpp gui/spectrum/filter/MeanBlurForm.h
        gui/spectrum/SpectrumFilterView.cpp gui/spectrum/SpectrumFilterView.h
        gui/spectrum/filter/MedianForm.cpp gui/spectrum/filter/MedianForm.h
        gui/spectrum/filter/FunctionFilterForm.cpp gui/spectrum/filter/FunctionFilterForm.h
        gui/options/MatrixExpression.cpp gui/options/MatrixExpression.h
        gui/options/MatrixInput.cpp gui/options/MatrixInput.h
        gui/options/MatrixSheet.cpp gui/options/MatrixSheet.h
        gui/spectrum/Spectrum3DView.cpp gui/spectrum/Spectrum3DView.h
        gui/spectrum/SpectrumView.cpp gui/spectrum/SpectrumView.h
        gui/spectrum/SpectrumMaskView.cpp gui/spectrum/SpectrumMaskView.h
        )

set(PARSER_SOURCES
        parser/PlanarParser.h
        parser/LineParser.h
        parser/ParametricParser.h
        parser/ImageFunctionParser.cpp parser/ImageFunctionParser.h
        )

set(PROJECT_SOURCES
        ${CORE_SOURCES}
        ${GUI_SOURCES}
        ${PARSER_SOURCES}
        ${UTILITY_SOURCES}
        )

add_executable(ImageProcessing
        ${PROJECT_SOURCES}
        )

target_link_libraries(ImageProcessing
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Charts
        Qt::DataVisualization
        muparser
        )

