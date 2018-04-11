/*
 * Your License or Copyright can go here
 */

#ifndef _ITKImageBase_h_
#define _ITKImageBase_h_

#include "SIMPLib/Common/SIMPLibSetGetMacros.h"
#include "SIMPLib/Filtering/AbstractFilter.h"
#include "SIMPLib/SIMPLib.h"

#include "ITKImageProcessing/ITKImageProcessingFilters/itkDream3DFilterInterruption.h"
#include "ITKImageProcessing/ITKImageProcessingFilters/itkDream3DImage.h"
#include "ITKImageProcessing/ITKImageProcessingFilters/itkInPlaceDream3DDataToImageFilter.h"
#include "ITKImageProcessing/ITKImageProcessingFilters/itkInPlaceImageToDream3DDataFilter.h"
#include "itkImageToImageFilter.h"

#include <itkCastImageFilter.h>
#include <itkNumericTraits.h>

// The sitkExplicitITK.h header must be AFTER any ITK includes above or
// the code will not compile on Windows. Further, windows does not seem
// to have the symbol loading issues that macOS has so lets just #define
// around it for macOS systems only.
#if defined(__APPLE__)
//  #include "sitkExplicitITK.h"
#endif

/**
 * @brief The ITKImageBase class. See [Filter documentation](@ref ITKImageBase) for details.
 */
class ITKImageBase : public AbstractFilter
{
  Q_OBJECT

public:
  // SIMPL_SHARED_POINTERS(ITKImageBase)
  // SIMPL_TYPE_MACRO_SUPER_OVERRIDE(ITKImageBase, AbstractFilter)

    ~ITKImageBase() override = default;
    
    /**
   * @brief execute Reimplemented from @see AbstractFilter class
   */
    void execute() override
    {
      initialize();
      this->dataCheckInternal();
      if(getErrorCondition() < 0)
      {
        return;
      }
      if(getCancel())
      {
        return;
      }
      this->filterInternal();
    }
    /**
  * @brief preflight Reimplemented from @see AbstractFilter class
  */
    void preflight() override
    {
      // These are the REQUIRED lines of CODE to make sure the filter behaves correctly
      setInPreflight(true);              // Set the fact that we are preflighting.
      emit preflightAboutToExecute();    // Emit this signal so that other widgets can do one file update
      emit updateFilterParameters(this); // Emit this signal to have the widgets push their values down to the filter
      this->dataCheckInternal();
      emit preflightExecuted(); // We are done preflighting this filter
      setInPreflight(false);    // Inform the system this filter is NOT in preflight mode anymore.
    }


  /**
   * @brief CastVec3ToITK Input type should be FloatVec3_t or IntVec3_t, Output
     type should be some kind of ITK "array" (itk::Size, itk::Index,...)
   */
  template <typename InputType, typename OutputType, typename ComponentType> 
  OutputType CastVec3ToITK(const InputType& inputVec3, unsigned int dimension) const
  {
    OutputType output;
    if(dimension > 0)
    {
      output[0] = static_cast<ComponentType>(inputVec3.x);
      if(dimension > 1)
      {
        output[1] = static_cast<ComponentType>(inputVec3.y);
        if(dimension > 2)
        {
          output[2] = static_cast<ComponentType>(inputVec3.z);
        }
      }
    }
    return output;
  }
  /**
   * @brief StaticCast Performs a static cast on a value. 'unused' type is to match 'CastStdToVec3' template format to simplify template declaration in conversion script.
   */
  template <typename InputType, typename OutputType, typename unused> 
  OutputType StaticCastScalar(const InputType& val) const
  {
    return static_cast<OutputType>(val);
  }

  /**
   * @brief CastStdToVec3 Input type should be std::vector<float> or std::vector<int>
     and Output type should be FloatVec3_t or IntVec3_t
   */
  template <typename InputType, typename OutputType, typename ComponentType> 
  OutputType CastStdToVec3(const InputType& inputVector) const
  {
    OutputType outputVec3;
    if(inputVector.size() > 0)
    {
      outputVec3.x = static_cast<ComponentType>(inputVector[0]);
      if(inputVector.size() > 1)
      {
        outputVec3.y = static_cast<ComponentType>(inputVector[1]);
        if(inputVector.size() > 2)
        {
          outputVec3.z = static_cast<ComponentType>(inputVector[2]);
        }
      }
    }
    return outputVec3;
  }

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
  ITKImageBase()
  {
    initialize();
  }


  /**
   * @brief dataCheck Checks for the appropriate parameter values and availability of arrays
   */

  void virtual dataCheckInternal() = 0;

  /**
   * @brief imageCheck checks if data array contains an image.
   */
  template <typename PixelType, unsigned int Dimension> 
  void imageCheck(const DataArrayPath &array_path)
  {
    using ValueType = typename itk::NumericTraits<PixelType>::ValueType ;
    // Check data array
    typename DataArray<ValueType>::WeakPointer cellArrayPtr;
    ValueType* cellArray;

    QVector<size_t> dims = ITKDream3DHelper::GetComponentsDimensions<PixelType>();
    cellArrayPtr = getDataContainerArray()->getPrereqArrayFromPath<DataArray<ValueType>, AbstractFilter>(
        this, array_path, dims); /* Assigns the shared_ptr<> to an instance variable that is a weak_ptr<> */
    if(nullptr != cellArrayPtr.lock()) /* Validate the Weak Pointer wraps a non-nullptr pointer to a DataArray<T> object */
    {
      cellArray = cellArrayPtr.lock()->getPointer(0);
    } /* Now assign the raw pointer to data from the DataArray<T> object */
    if(getErrorCondition() < 0)
    {
      return;
    }

    ImageGeom::Pointer image = getDataContainerArray()->getDataContainer(array_path.getDataContainerName())->getPrereqGeometry<ImageGeom, AbstractFilter>(this);
    if(nullptr == image)
    {
      setErrorCondition(-1);
      notifyErrorMessage(getHumanLabel(), "Array path does not contain image geometry.", getErrorCondition());
    }
  }

  /**
  * @brief Applies the filter
  */
  template <typename InputPixelType, typename OutputPixelType, unsigned int Dimension, typename FilterType> 
  void filter(FilterType* filter, const std::string &outputArrayName, bool saveAsNewArray, const DataArrayPath &selectedArray)
  {
    try
    {
      DataContainer::Pointer dc = getDataContainerArray()->getDataContainer(selectedArray.getDataContainerName());

      using OutputImageType = itk::Dream3DImage<OutputPixelType, Dimension> ;
      using toITKType = itk::InPlaceDream3DDataToImageFilter<InputPixelType, Dimension> ;
      // Create a Bridge to wrap an existing DREAM.3D array with an ItkImage container
      typename toITKType::Pointer toITK = toITKType::New();
      toITK->SetInput(dc);
      toITK->SetInPlace(true);
      toITK->SetAttributeMatrixArrayName(selectedArray.getAttributeMatrixName().toStdString());
      toITK->SetDataArrayName(selectedArray.getDataArrayName().toStdString());

      itk::Dream3DFilterInterruption::Pointer interruption = itk::Dream3DFilterInterruption::New();
      interruption->SetFilter(this);

      // Set up filter
      filter->SetInput(toITK->GetOutput());
      filter->AddObserver(itk::ProgressEvent(), interruption);
      filter->Update();

      typename OutputImageType::Pointer image = OutputImageType::New();
      image = filter->GetOutput();
      image->DisconnectPipeline();

      if(!saveAsNewArray)
      {
        AttributeMatrix::Pointer attrMat = dc->getAttributeMatrix(selectedArray.getAttributeMatrixName());
        // Remove the original input data array
        attrMat->removeAttributeArray(selectedArray.getDataArrayName());
      }

      using toDream3DType = itk::InPlaceImageToDream3DDataFilter<OutputPixelType, Dimension> ;
      typename toDream3DType::Pointer toDream3DFilter = toDream3DType::New();
      toDream3DFilter->SetInput(image);
      toDream3DFilter->SetInPlace(true);
      toDream3DFilter->SetAttributeMatrixArrayName(selectedArray.getAttributeMatrixName().toStdString());
      toDream3DFilter->SetDataArrayName(outputArrayName);
      toDream3DFilter->SetDataContainer(dc);
      toDream3DFilter->Update();
    } catch(itk::ExceptionObject& err)
    {
      setErrorCondition(-55555);
      QString errorMessage = "ITK exception was thrown while filtering input image: %1";
      notifyErrorMessage(getHumanLabel(), errorMessage.arg(err.GetDescription()), getErrorCondition());
      return;
    }

    notifyStatusMessage(getHumanLabel(), "Complete");
  }

  /**
  * @brief Applies the filter, casting the input to float
  */
  template <typename InputPixelType, typename OutputPixelType, unsigned int Dimension, typename FilterType, typename FloatImageType> 
  void filterCastToFloat(FilterType* filter, const std::string &outputArrayName, bool saveAsNewArray, const DataArrayPath &selectedArray)
  {
    try
    {
      DataContainer::Pointer dc = getDataContainerArray()->getDataContainer(selectedArray.getDataContainerName());

      using toITKType = itk::InPlaceDream3DDataToImageFilter<InputPixelType, Dimension>;
      // Create a Bridge to wrap an existing DREAM.3D array with an ItkImage container
      typename toITKType::Pointer toITK = toITKType::New();
      toITK->SetInput(dc);
      toITK->SetInPlace(true);
      toITK->SetAttributeMatrixArrayName(selectedArray.getAttributeMatrixName().toStdString());
      toITK->SetDataArrayName(selectedArray.getDataArrayName().toStdString());

      itk::Dream3DFilterInterruption::Pointer interruption = itk::Dream3DFilterInterruption::New();
      interruption->SetFilter(this);

      using InputImageType = typename toITKType::ImageType ;
      using CasterToType = itk::CastImageFilter<InputImageType, FloatImageType> ;
      typename CasterToType::Pointer casterTo = CasterToType::New();
      casterTo->SetInput(toITK->GetOutput());

      // Set up filter
      filter->SetInput(casterTo->GetOutput());
      filter->AddObserver(itk::ProgressEvent(), interruption);

      using OutputImageType = itk::Dream3DImage<OutputPixelType, Dimension> ;
      using CasterFromType = itk::CastImageFilter<FloatImageType, OutputImageType> ;
      typename CasterFromType::Pointer casterFrom = CasterFromType::New();
      casterFrom->SetInput(filter->GetOutput());
      casterFrom->Update();

      typename OutputImageType::Pointer image = OutputImageType::New();
      image = casterFrom->GetOutput();
      image->DisconnectPipeline();

      if(!saveAsNewArray)
      {
        AttributeMatrix::Pointer attrMat = dc->getAttributeMatrix(selectedArray.getAttributeMatrixName());
        // Remove the original input data array
        attrMat->removeAttributeArray(selectedArray.getDataArrayName());
      }

      using toDream3DType = itk::InPlaceImageToDream3DDataFilter<OutputPixelType, Dimension> ;
      typename toDream3DType::Pointer toDream3DFilter = toDream3DType::New();
      toDream3DFilter->SetInput(image);
      toDream3DFilter->SetInPlace(true);
      toDream3DFilter->SetAttributeMatrixArrayName(selectedArray.getAttributeMatrixName().toStdString());
      toDream3DFilter->SetDataArrayName(outputArrayName);
      toDream3DFilter->SetDataContainer(dc);
      toDream3DFilter->Update();
    } catch(itk::ExceptionObject& err)
    {
      setErrorCondition(-55556);
      QString errorMessage = "ITK exception was thrown while filtering input image: %1";
      notifyErrorMessage(getHumanLabel(), errorMessage.arg(err.GetDescription()), getErrorCondition());
      return;
    }

    notifyStatusMessage(getHumanLabel(), "Complete");
  }

  /**
  * @brief CheckIntegerEntry: Input types can only be of certain types (float, double, bool, int).
    For the other type, we have to use one of this primitive type, and verify that the
    value corresponds to what is expected.
    The 3rd parameter, 'bool' is given to match the definition of CheckVectorEntry. This allows
    to use a dictionary in Python to choose between the 2 functions.
  */
  template <typename VarType, typename SubsType> 
  void CheckIntegerEntry(SubsType value, const QString &name, bool /* b */)
  {
    using ValueType = typename itk::NumericTraits<VarType>::ValueType ;
    SubsType lowest = static_cast<SubsType>(std::numeric_limits<ValueType>::lowest());
    SubsType max = static_cast<SubsType>(std::numeric_limits<ValueType>::max());
    if(value < lowest || value > max || value != floor(value))
    {
      setErrorCondition(-1);
      QString errorMessage = name + QString(" must be greater or equal than %1 and lesser or equal than %2 and an integer");
      notifyErrorMessage(getHumanLabel(), errorMessage.arg(lowest).arg(max), getErrorCondition());
    }
  }

  /**
  * @brief CheckVectorEntry: Vector input types can only be of certain types (float or int).
    For the other type, we have to use one of this primitive type, and verify that the
    value corresponds to what is expected.
  */
  template <typename VarType, typename SubsType> 
  void CheckVectorEntry(SubsType value, const QString &name, bool integer)
  {
    using ValueType = typename itk::NumericTraits<VarType>::ValueType;
    auto lowest = static_cast<float>(std::numeric_limits<ValueType>::lowest());
    auto max = static_cast<float>(std::numeric_limits<ValueType>::max());
    if(value.x < lowest || value.x > max || (integer && value.x != floor(value.x)) || value.y < lowest || value.y > max || (integer && value.y != floor(value.y)) || value.z < lowest ||
       value.z > max || (integer && value.z != floor(value.z)))
    {
      setErrorCondition(-1);
      QString errorMessage = name + QString(" values must be greater or equal than %1 and lesser or equal than %2");
      if(integer)
      {
        errorMessage += QString(" and integers");
      }
      notifyErrorMessage(getHumanLabel(), errorMessage.arg(lowest).arg(max), getErrorCondition());
    }
  }

  /**
  * @brief Check if image type corresponds to requirements
  */
  bool checkImageType(const QVector<QString>& types, const DataArrayPath& path)
  {
    IDataArray::Pointer ptr = getDataContainerArray()->getPrereqIDataArrayFromPath<IDataArray, AbstractFilter>(this, path);
    if(nullptr != ptr)
    {
      if(types.indexOf(ptr->getTypeAsString()) != -1)
      {
        return true;
      }
      setErrorCondition(-12);
      QString errorMessage = "Wrong data type in %1. Expected %2. Try CastImageFilter or RescaleImageFilter to convert input data to a supported type.";
      QString stringTypes = QStringList(types.toList()).join(",");
      notifyErrorMessage(getHumanLabel(), errorMessage.arg(path.serialize()).arg(stringTypes), getErrorCondition());
    }
    // If no data container, return false, but do not set any error condition.
    return false;
  }

  /**
  * @brief Applies the filter
  */
  void virtual filterInternal() = 0;

  /**
   * @brief Initializes all the private instance variables.
   */
  void initialize()
  {
    setErrorCondition(0);
    setWarningCondition(0);
    setCancel(false);
  }

  private:
  
  public:
  ITKImageBase(const ITKImageBase&) = delete; // Copy Constructor Not Implemented
  ITKImageBase(ITKImageBase&&) = delete;      // Move Constructor Not Implemented
  ITKImageBase& operator=(const ITKImageBase&) = delete; // Copy Assignment Not Implemented
  ITKImageBase& operator=(ITKImageBase&&) = delete;      // Move Assignment Not Implemented
};

#endif /* _ITKImageBase_H_ */
