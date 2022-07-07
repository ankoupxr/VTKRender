//#include "Image.h"
//
//vtkSmartPointer<vtkDICOMImageReader> VTKRender::Image::getImageReader() const
//{
//	if (m_imageReader)
//	{
//		return vtkSmartPointer<vtkDICOMImageReader>(m_imageReader);
//	}
//	vtkNew<vtkDICOMImageReader> m_imageReader;
//	m_imageReader->SetFileName(m_path.c_str());
//	m_imageReader->Update();
//	return m_imageReader;
//}
//
////-----------------------------------------------------------------------------
//bool VTKRender::Image::equal(Image* t_image) const
//{
//	return getParentObject() == t_image->getParentObject() &&
//		getImagePath() == t_image->getImagePath() &&
//		getSOPInstanceUID() == t_image->getSOPInstanceUID() &&
//		getClassUID() == t_image->getClassUID() &&
//		getFrameOfRefernceID() == t_image->getFrameOfRefernceID() &&
//		getModality() == t_image->getModality() &&
//		getWindowCenter() == t_image->getWindowCenter() &&
//		getWindowWidth() == t_image->getWindowWidth() &&
//		getRows() == t_image->getRows() &&
//		getColumns() == t_image->getColumns() &&
//		getNumberOfFrames() == t_image->getNumberOfFrames() &&
//		getSliceLocation() == t_image->getSliceLocation() &&
//		getAcquisitionNumber() == t_image->getAcquisitionNumber() &&
//		getIsMultiFrame() == t_image->getIsMultiFrame();
//}
//
////-----------------------------------------------------------------------------
//bool VTKRender::Image::isLess(Image* t_lhs, Image* t_rhs)
//{
//	if (t_lhs->getInstanceNumber() == t_rhs->getInstanceNumber())
//	{
//		return t_lhs->getSliceLocation() < t_rhs->getSliceLocation();
//	}
//	return t_lhs->getInstanceNumber() < t_rhs->getInstanceNumber();
//}