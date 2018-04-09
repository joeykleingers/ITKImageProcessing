// File automatically generated

/*
 * Your License or Copyright can go here
 */

#ifndef _ITKMeanProjectionImage_h_
#define _ITKMeanProjectionImage_h_

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Winconsistent-missing-override"
#endif

#include "ITKImageProcessingBase.h"

#include "SIMPLib/Common/SIMPLibSetGetMacros.h"
#include "SIMPLib/SIMPLib.h"

// Auto includes
#include <SIMPLib/FilterParameters/DoubleFilterParameter.h>
#include <itkMeanProjectionImageFilter.h>


/**
 * @brief The ITKMeanProjectionImage class. See [Filter documentation](@ref ITKMeanProjectionImage) for details.
 */
class ITKMeanProjectionImage : public ITKImageProcessingBase
{
  Q_OBJECT
  PYB11_CREATE_BINDINGS(ITKMeanProjectionImage SUPERCLASS ITKImageProcessingBase)
  PYB11_PROPERTY(double ProjectionDimension READ getProjectionDimension WRITE setProjectionDimension)

public:
  SIMPL_SHARED_POINTERS(ITKMeanProjectionImage)
  SIMPL_FILTER_NEW_MACRO(ITKMeanProjectionImage)
  SIMPL_TYPE_MACRO_SUPER_OVERRIDE(ITKMeanProjectionImage, AbstractFilter)

  virtual ~ITKMeanProjectionImage();

  SIMPL_FILTER_PARAMETER(double, ProjectionDimension)
  Q_PROPERTY(double ProjectionDimension READ getProjectionDimension WRITE setProjectionDimension)


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
  ITKMeanProjectionImage();

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
  ITKMeanProjectionImage(const ITKMeanProjectionImage&) = delete;    // Copy Constructor Not Implemented
  void operator=(const ITKMeanProjectionImage&) = delete;            // Move assignment Not Implemented
};

#ifdef __clang__
#pragma clang diagnostic pop
#endif

#endif /* _ITKMeanProjectionImage_H_ */
