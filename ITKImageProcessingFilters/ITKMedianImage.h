// File automatically generated

/*
 * Your License or Copyright can go here
 */

#pragma once

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Winconsistent-missing-override"
#endif

#include <memory>

#include "ITKImageProcessingBase.h"

#include "SIMPLib/SIMPLib.h"

// Auto includes
#include <SIMPLib/FilterParameters/FloatVec3FilterParameter.h>
#include <itkMedianImageFilter.h>

#include "ITKImageProcessing/ITKImageProcessingDLLExport.h"

/**
 * @brief The ITKMedianImage class. See [Filter documentation](@ref ITKMedianImage) for details.
 */
class ITKImageProcessing_EXPORT ITKMedianImage : public ITKImageProcessingBase
{
  Q_OBJECT

  // Start Python bindings declarations
  PYB11_BEGIN_BINDINGS(ITKMedianImage SUPERCLASS ITKImageProcessingBase)
  PYB11_FILTER()
  PYB11_SHARED_POINTERS(ITKMedianImage)
  PYB11_FILTER_NEW_MACRO(ITKMedianImage)
  PYB11_PROPERTY(FloatVec3Type Radius READ getRadius WRITE setRadius)
  PYB11_END_BINDINGS()
  // End Python bindings declarations

public:
  using Self = ITKMedianImage;
  using Pointer = std::shared_ptr<Self>;
  using ConstPointer = std::shared_ptr<const Self>;
  using WeakPointer = std::weak_ptr<Self>;
  using ConstWeakPointer = std::weak_ptr<const Self>;
  static Pointer NullPointer();

  static std::shared_ptr<ITKMedianImage> New();

  /**
   * @brief Returns the name of the class for ITKMedianImage
   */
  QString getNameOfClass() const override;
  /**
   * @brief Returns the name of the class for ITKMedianImage
   */
  static QString ClassName();

  ~ITKMedianImage() override;

  /**
   * @brief Setter property for Radius
   */
  void setRadius(const FloatVec3Type& value);
  /**
   * @brief Getter property for Radius
   * @return Value of Radius
   */
  FloatVec3Type getRadius() const;
  Q_PROPERTY(FloatVec3Type Radius READ getRadius WRITE setRadius)

  /**
   * @brief newFilterInstance Reimplemented from @see AbstractFilter class
   */
  AbstractFilter::Pointer newFilterInstance(bool copyFilterParameters) const override;

  /**
   * @brief getHumanLabel Reimplemented from @see AbstractFilter class
   */
  QString getHumanLabel() const override;

  /**
   * @brief getSubGroupName Reimplemented from @see AbstractFilter class
   */
  QString getSubGroupName() const override;

  /**
   * @brief getUuid Return the unique identifier for this filter.
   * @return A QUuid object.
   */
  QUuid getUuid() const override;

  /**
   * @brief setupFilterParameters Reimplemented from @see AbstractFilter class
   */
  void setupFilterParameters() override;

  /**
   * @brief readFilterParameters Reimplemented from @see AbstractFilter class
   */
  void readFilterParameters(AbstractFilterParametersReader* reader, int index) override;

protected:
  ITKMedianImage();

  /**
   * @brief dataCheckInternal overloads dataCheckInternal in ITKImageBase and calls templated dataCheck
   */
  void dataCheck() override;

  /**
   * @brief dataCheck Checks for the appropriate parameter values and availability of arrays
   */
  template <typename InputImageType, typename OutputImageType, unsigned int Dimension>
  void dataCheckImpl();

  /**
   * @brief filterInternal overloads filterInternal in ITKImageBase and calls templated filter
   */
  void filterInternal() override;

  /**
   * @brief Applies the filter
   */
  template <typename InputImageType, typename OutputImageType, unsigned int Dimension>
  void filter();

public:
  ITKMedianImage(const ITKMedianImage&) = delete;            // Copy Constructor Not Implemented
  ITKMedianImage(ITKMedianImage&&) = delete;                 // Move Constructor Not Implemented
  ITKMedianImage& operator=(const ITKMedianImage&) = delete; // Copy Assignment Not Implemented
  ITKMedianImage& operator=(ITKMedianImage&&) = delete;      // Move Assignment Not Implemented

private:
  FloatVec3Type m_Radius = {};
};

#ifdef __clang__
#pragma clang diagnostic pop
#endif
