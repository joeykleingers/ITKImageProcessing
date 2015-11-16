/*
 * Your License should go here
 */
#ifndef _ZeissImportConstants_H_
#define _ZeissImportConstants_H_

#include <QtCore/QString>

#define ZEISS_HDF_SUPPORT 1

/**
* @brief This namespace is used to define some Constants for the plugin itself.
*/
namespace ZeissImportConstants
{
  const QString ZeissImportPluginFile("ZeissImportPlugin");
  const QString ZeissImportPluginDisplayName("ZeissImport");
  const QString ZeissImportBaseName("ZeissImport");

  namespace FilterGroups
  {
    const QString ZeissImportFilters("Zeiss Import");
  }

  namespace Xml
  {
    static const QString Tags("Tags");
    static const QString Count("Count");
  }

  namespace PolynomialOrder
  {
    const unsigned int NumConsts2ndOrder = 6;
  }

/* EVERY Filter that gets added to this namespace should also be added to the
* unit test to make sure we keep up with any name changes in the ImageProcessing
* Plugin
*/
  namespace ImageProcessingFilters
  {

    static const QString k_ReadImageFilterClassName("ItkReadImage");
    static const QString k_RgbToGrayFilterClassName("ItkRGBToGray");
  }
}

/**
* @brief Use this namespace to define any custom GUI widgets that collect FilterParameters
* for a filter. Do NOT define general reusable widgets here.
*/
namespace FilterParameterWidgetType
{

/*  const QString SomeCustomWidget("SomeCustomWidget"); */

}




#endif
