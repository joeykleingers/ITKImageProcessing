// File automatically generated

/*
 * Your License or Copyright can go here
 */

#ifndef _ITKDiscreteGaussianImage_h_
#define _ITKDiscreteGaussianImage_h_

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Winconsistent-missing-override"
#endif

#include "ITKImageProcessingBase.h"

#include "SIMPLib/Common/SIMPLibSetGetMacros.h"
#include "SIMPLib/SIMPLib.h"

// Auto includes
#include <SIMPLib/FilterParameters/BooleanFilterParameter.h>
#include <SIMPLib/FilterParameters/DoubleFilterParameter.h>
#include <SIMPLib/FilterParameters/FloatVec3FilterParameter.h>
#include <itkDiscreteGaussianImageFilter.h>


/**
 * @brief The ITKDiscreteGaussianImage class. See [Filter documentation](@ref ITKDiscreteGaussianImage) for details.
 */
class ITKDiscreteGaussianImage : public ITKImageProcessingBase
{
  Q_OBJECT
  PYB11_CREATE_BINDINGS(ITKDiscreteGaussianImage SUPERCLASS ITKImageProcessingBase)
  PYB11_PROPERTY(FloatVec3_t Variance READ getVariance WRITE setVariance)
  PYB11_PROPERTY(double MaximumKernelWidth READ getMaximumKernelWidth WRITE setMaximumKernelWidth)
  PYB11_PROPERTY(FloatVec3_t MaximumError READ getMaximumError WRITE setMaximumError)
  PYB11_PROPERTY(bool UseImageSpacing READ getUseImageSpacing WRITE setUseImageSpacing)

public:
  SIMPL_SHARED_POINTERS(ITKDiscreteGaussianImage)
  SIMPL_STATIC_NEW_MACRO(ITKDiscreteGaussianImage)
   SIMPL_TYPE_MACRO_SUPER_OVERRIDE(ITKDiscreteGaussianImage, AbstractFilter)

  virtual ~ITKDiscreteGaussianImage();

  SIMPL_FILTER_PARAMETER(FloatVec3_t, Variance)
  Q_PROPERTY(FloatVec3_t Variance READ getVariance WRITE setVariance)

  SIMPL_FILTER_PARAMETER(double, MaximumKernelWidth)
  Q_PROPERTY(double MaximumKernelWidth READ getMaximumKernelWidth WRITE setMaximumKernelWidth)

  SIMPL_FILTER_PARAMETER(FloatVec3_t, MaximumError)
  Q_PROPERTY(FloatVec3_t MaximumError READ getMaximumError WRITE setMaximumError)

  SIMPL_FILTER_PARAMETER(bool, UseImageSpacing)
  Q_PROPERTY(bool UseImageSpacing READ getUseImageSpacing WRITE setUseImageSpacing)


  /**
   * @brief newFilterInstance Reimplemented from @see AbstractFilter class
   */
  AbstractFilter::Pointer newFilterInstance(bool copyFilterParameters) const override;

  /**
   * @brief getHumanLabel Reimplemented from @see AbstractFilter class
   */
  const QString getHumanLabel() const override;

  /**
   * @brief getSubGroupName Reimplemented from @see AbstractFilter class
   */
  const QString getSubGroupName() const override;

  /**
   * @brief getUuid Return the unique identifier for this filter.
   * @return A QUuid object.
   */
  const QUuid getUuid() override;

  /**
   * @brief setupFilterParameters Reimplemented from @see AbstractFilter class
   */
  void setupFilterParameters() override;

  /**
   * @brief readFilterParameters Reimplemented from @see AbstractFilter class
   */
  void readFilterParameters(AbstractFilterParametersReader* reader, int index) override;

protected:
  ITKDiscreteGaussianImage();

  /**
   * @brief dataCheckInternal overloads dataCheckInternal in ITKImageBase and calls templated dataCheck
   */
  void virtual dataCheckInternal() override;

  /**
   * @brief dataCheck Checks for the appropriate parameter values and availability of arrays
   */
  template <typename InputImageType, typename OutputImageType, unsigned int Dimension> void dataCheck();

  /**
  * @brief filterInternal overloads filterInternal in ITKImageBase and calls templated filter
  */
  void virtual filterInternal() override;

  /**
  * @brief Applies the filter
  */
  template <typename InputImageType, typename OutputImageType, unsigned int Dimension> void filter();

private:
  ITKDiscreteGaussianImage(const ITKDiscreteGaussianImage&) = delete;    // Copy Constructor Not Implemented
  void operator=(const ITKDiscreteGaussianImage&) = delete;              // Move assignment Not Implemented
};

#ifdef __clang__
#pragma clang diagnostic pop
#endif

#endif /* _ITKDiscreteGaussianImage_H_ */
