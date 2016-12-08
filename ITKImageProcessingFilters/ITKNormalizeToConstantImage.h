// File automatically generated

/*
 * Your License or Copyright can go here
 */

#ifndef _ITKNormalizeToConstantImage_h_
#define _ITKNormalizeToConstantImage_h_

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Winconsistent-missing-override"

#include "ITKImageBase.h"

#include "SIMPLib/SIMPLib.h"
#include "SIMPLib/Common/SIMPLibSetGetMacros.h"

//Auto includes
#include <SIMPLib/FilterParameters/DoubleFilterParameter.h>
#include <itkNormalizeToConstantImageFilter.h>


/**
 * @brief The ITKNormalizeToConstantImage class. See [Filter documentation](@ref ITKNormalizeToConstantImage) for details.
 */
class ITKNormalizeToConstantImage : public ITKImageBase
{
  Q_OBJECT

  public:
    SIMPL_SHARED_POINTERS(ITKNormalizeToConstantImage)
    SIMPL_STATIC_NEW_MACRO(ITKNormalizeToConstantImage)
    SIMPL_TYPE_MACRO_SUPER_OVERRIDE(ITKNormalizeToConstantImage, AbstractFilter)

    virtual ~ITKNormalizeToConstantImage();

    SIMPL_FILTER_PARAMETER(double, Constant)
    Q_PROPERTY(double Constant READ getConstant WRITE setConstant)



    /**
     * @brief newFilterInstance Reimplemented from @see AbstractFilter class
     */
    virtual AbstractFilter::Pointer newFilterInstance(bool copyFilterParameters) override;

    /**
     * @brief getHumanLabel Reimplemented from @see AbstractFilter class
     */
    virtual const QString getHumanLabel() override;

    /**
     * @brief getSubGroupName Reimplemented from @see AbstractFilter class
     */
    virtual const QString getSubGroupName() override;
    
    /**
     * @brief setupFilterParameters Reimplemented from @see AbstractFilter class
     */
    virtual void setupFilterParameters() override;

    /**
     * @brief readFilterParameters Reimplemented from @see AbstractFilter class
     */
    virtual void readFilterParameters(AbstractFilterParametersReader* reader, int index) override;

  protected:
    ITKNormalizeToConstantImage();

    /**
     * @brief dataCheckInternal overloads dataCheckInternal in ITKImageBase and calls templated dataCheck
     */
    void virtual dataCheckInternal() override;

    /**
     * @brief dataCheck Checks for the appropriate parameter values and availability of arrays
     */
    template<typename InputImageType, typename OutputImageType, unsigned int Dimension>
    void dataCheck();

    /**
    * @brief filterInternal overloads filterInternal in ITKImageBase and calls templated filter
    */
    void virtual filterInternal() override;

    /**
    * @brief Applies the filter
    */
    template<typename InputImageType, typename OutputImageType, unsigned int Dimension>
    void filter();

  private:

    ITKNormalizeToConstantImage(const ITKNormalizeToConstantImage&); // Copy Constructor Not Implemented
    void operator=(const ITKNormalizeToConstantImage&); // Operator '=' Not Implemented
};

#pragma clang diagnostic pop

#endif /* _ITKNormalizeToConstantImage_H_ */
