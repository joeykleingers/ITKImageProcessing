/*
 * Your License or Copyright can go here
 */

#ifndef _ITKImageBase_h_
#define _ITKImageBase_h_

#include "SIMPLib/SIMPLib.h"
#include "SIMPLib/Common/AbstractFilter.h"
#include "SIMPLib/Common/SIMPLibSetGetMacros.h"

#include "itkImageToImageFilter.h"
#include "ITKImageProcessing/ITKImageProcessingFilters/itkDream3DImage.h"
#include "ITKImageProcessing/ITKImageProcessingFilters/itkInPlaceDream3DDataToImageFilter.h"
#include "ITKImageProcessing/ITKImageProcessingFilters/itkInPlaceImageToDream3DDataFilter.h"
#include "ITKImageProcessing/ITKImageProcessingFilters/itkDream3DFilterInterruption.h"

/**
 * @brief The ITKImageBase class. See [Filter documentation](@ref ITKImageBase) for details.
 */
class ITKImageBase : public AbstractFilter
{
  Q_OBJECT

  public:
    SIMPL_SHARED_POINTERS(ITKImageBase)
    SIMPL_TYPE_MACRO_SUPER(ITKImageBase, AbstractFilter)

    virtual ~ITKImageBase();

    SIMPL_FILTER_PARAMETER(DataArrayPath, SelectedCellArrayPath)
    Q_PROPERTY(DataArrayPath SelectedCellArrayPath READ getSelectedCellArrayPath WRITE setSelectedCellArrayPath)

    SIMPL_FILTER_PARAMETER(QString, NewCellArrayName)
    Q_PROPERTY(QString NewCellArrayName READ getNewCellArrayName WRITE setNewCellArrayName)

    SIMPL_FILTER_PARAMETER(bool, SaveAsNewArray)
    Q_PROPERTY(bool SaveAsNewArray READ getSaveAsNewArray WRITE setSaveAsNewArray)

    /**
     * @brief getCompiledLibraryName Reimplemented from @see AbstractFilter class
     */
    virtual const QString getCompiledLibraryName();

    /**
     * @brief getBrandingString Returns the branding string for the filter, which is a tag
     * used to denote the filter's association with specific plugins
     * @return Branding string
    */
    virtual const QString getBrandingString();

    /**
     * @brief getFilterVersion Returns a version string for this filter. Default
     * value is an empty string.
     * @return
     */
    virtual const QString getFilterVersion();

    /**
     * @brief newFilterInstance Reimplemented from @see AbstractFilter class
     */
    virtual AbstractFilter::Pointer newFilterInstance(bool copyFilterParameters) = 0;

    /**
     * @brief getGroupName Reimplemented from @see AbstractFilter class
     */
    virtual const QString getGroupName();

    /**
     * @brief getSubGroupName Reimplemented from @see AbstractFilter class
     */
    virtual const QString getSubGroupName();

    /**
     * @brief getHumanLabel Reimplemented from @see AbstractFilter class
     */
    virtual const QString getHumanLabel() = 0;

    /**
     * @brief setupFilterParameters Reimplemented from @see AbstractFilter class
     */
    virtual void setupFilterParameters() = 0;

    /**
     * @brief readFilterParameters Reimplemented from @see AbstractFilter class
     */
    virtual void readFilterParameters(AbstractFilterParametersReader* reader, int index) = 0;

    /**
     * @brief execute Reimplemented from @see AbstractFilter class
     */
    virtual void execute();

    /**
    * @brief preflight Reimplemented from @see AbstractFilter class
    */
    virtual void preflight();

  signals:
    /**
     * @brief updateFilterParameters Emitted when the Filter requests all the latest Filter parameters
     * be pushed from a user-facing control (such as a widget)
     * @param filter Filter instance pointer 
     */
    void updateFilterParameters(AbstractFilter* filter);

    /**
     * @brief parametersChanged Emitted when any Filter parameter is changed internally
     */
    void parametersChanged();

    /**
     * @brief preflightAboutToExecute Emitted just before calling dataCheck()
     */
    void preflightAboutToExecute();

    /**
     * @brief preflightExecuted Emitted just after calling dataCheck()
     */
    void preflightExecuted();

  protected:
    ITKImageBase();

    /**
     * @brief dataCheck Checks for the appropriate parameter values and availability of arrays
     */
    void virtual dataCheckInternal() = 0;

    /**
     * @brief dataCheck Checks for the appropriate parameter values and availability of arrays
     */
    template<typename PixelType, unsigned int Dimension>
    void dataCheck()
    {
      // Check data array
      typename DataArray<PixelType>::WeakPointer selectedCellArrayPtr;
      PixelType* selectedCellArray;

      DataArrayPath tempPath;

      QVector<size_t> dims(1, 1);
      selectedCellArrayPtr = getDataContainerArray()->getPrereqArrayFromPath<DataArray<PixelType>, AbstractFilter>(this, getSelectedCellArrayPath(), dims); /* Assigns the shared_ptr<> to an instance variable that is a weak_ptr<> */
      if (nullptr != selectedCellArrayPtr.lock().get()) /* Validate the Weak Pointer wraps a non-nullptr pointer to a DataArray<T> object */
      {
        selectedCellArray = selectedCellArrayPtr.lock()->getPointer(0);
      } /* Now assign the raw pointer to data from the DataArray<T> object */
      if (getErrorCondition() < 0) { return; }

      ImageGeom::Pointer image = getDataContainerArray()->getDataContainer(getSelectedCellArrayPath().getDataContainerName())->getPrereqGeometry<ImageGeom, AbstractFilter>(this);
      if (getErrorCondition() < 0 || nullptr == image.get()) { return; }

      if (m_SaveAsNewArray == true)
      {
        tempPath.update(getSelectedCellArrayPath().getDataContainerName(), getSelectedCellArrayPath().getAttributeMatrixName(), getNewCellArrayName());
        m_NewCellArrayPtr = getDataContainerArray()->createNonPrereqArrayFromPath<DataArray<PixelType>, AbstractFilter, PixelType>(this, tempPath, 0, dims); /* Assigns the shared_ptr<> to an instance variable that is a weak_ptr<> */
        if (nullptr != m_NewCellArrayPtr.lock().get()) /* Validate the Weak Pointer wraps a non-nullptr pointer to a DataArray<T> object */
        {
          m_NewCellArray = m_NewCellArrayPtr.lock()->getVoidPointer(0);
        } /* Now assign the raw pointer to data from the DataArray<T> object */
      }
      else
      {
        m_NewCellArrayPtr = DataArray<PixelType>::NullPointer();
        m_NewCellArray = nullptr;
      }
    }

    /**
    * @brief Applies the filter
    */
    template<typename PixelType, unsigned int Dimension, typename FilterType>
    void filter(FilterType* filter)
    {
      try
    {
      DataArrayPath dap = getSelectedCellArrayPath();
      DataContainer::Pointer dc = getDataContainerArray()->getDataContainer(dap.getDataContainerName());

      typedef itk::Dream3DImage<PixelType, Dimension> ImageType;
      typedef itk::InPlaceDream3DDataToImageFilter<PixelType, Dimension> toITKType;
      // Create a Bridge to wrap an existing DREAM.3D array with an ItkImage container
      typename toITKType::Pointer toITK = toITKType::New();
      toITK->SetInput(dc);
      toITK->SetInPlace(true);
      toITK->SetAttributeMatrixArrayName(getSelectedCellArrayPath().getAttributeMatrixName().toStdString());
      toITK->SetDataArrayName(getSelectedCellArrayPath().getDataArrayName().toStdString());

      itk::Dream3DFilterInterruption::Pointer interruption = itk::Dream3DFilterInterruption::New();
      interruption->SetFilter(this);

      // Set up filter
      filter->SetInput(filter->GetOutput());
      filter->AddObserver(itk::ProgressEvent(), interruption);
      filter->Update();

      typename ImageType::Pointer image = ImageType::New();
      image = filter->GetOutput();
      image->DisconnectPipeline();
      std::string outputArrayName(getNewCellArrayName().toStdString());

      if (getSaveAsNewArray() == false)
      {
        outputArrayName = getSelectedCellArrayPath().getDataArrayName().toStdString();
        AttributeMatrix::Pointer attrMat = dc->getAttributeMatrix(getSelectedCellArrayPath().getAttributeMatrixName());
        // Remove the original input data array
        attrMat->removeAttributeArray(getSelectedCellArrayPath().getDataArrayName());
      }

      typename itk::InPlaceImageToDream3DDataFilter<PixelType, Dimension>::Pointer toDream3DFilter = itk::InPlaceImageToDream3DDataFilter<PixelType, Dimension>::New();
      toDream3DFilter->SetInput(image);
      toDream3DFilter->SetInPlace(true);
      toDream3DFilter->SetAttributeMatrixArrayName(getSelectedCellArrayPath().getAttributeMatrixName().toStdString());
      toDream3DFilter->SetDataArrayName(outputArrayName);
      toDream3DFilter->SetDataContainer(dc);
      toDream3DFilter->Update();


    }
    catch (itk::ExceptionObject & err)
    {
      setErrorCondition(-5);
      QString errorMessage = "ITK exception was thrown while filtering input image: %1";
      notifyErrorMessage(getHumanLabel(), errorMessage.arg(err.GetDescription()), getErrorCondition());
      return;
    }

    notifyStatusMessage(getHumanLabel(), "Complete");

}

    /**
    * @brief Applies the filter
    */
    void virtual filterInternal() = 0 ;

    /**
     * @brief Initializes all the private instance variables.
     */
    void initialize();

  private:

    DEFINE_IDATAARRAY_VARIABLE(NewCellArray)

    ITKImageBase(const ITKImageBase&); // Copy Constructor Not Implemented
    void operator=(const ITKImageBase&); // Operator '=' Not Implemented
};

#endif /* _ITKImageBase_H_ */