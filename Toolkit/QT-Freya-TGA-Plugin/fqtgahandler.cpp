/****************************************************************************
 **
 ** Copyright (C) 2008 Nokia Corporation and/or its subsidiary(-ies).
 ** Contact: Qt Software Information (qt-info@nokia.com)
 **
 ** This file is part of the plugins of the Qt Toolkit.
 **
 ** Commercial Usage
 ** Licensees holding valid Qt Commercial licenses may use this file in
 ** accordance with the Qt Commercial License Agreement provided with the
 ** Software or, alternatively, in accordance with the terms contained in
 ** a written agreement between you and Nokia.
 **
 **
 ** GNU General Public License Usage
 ** Alternatively, this file may be used under the terms of the GNU
 ** General Public License versions 2.0 or 3.0 as published by the Free
 ** Software Foundation and appearing in the file LICENSE.GPL included in
 ** the packaging of this file.  Please review the following information
 ** to ensure GNU General Public Licensing requirements will be met:
 ** http://www.fsf.org/licensing/licenses/info/GPLv2.html and
 ** http://www.gnu.org/copyleft/gpl.html.  In addition, as a special
 ** exception, Nokia gives you certain additional rights. These rights
 ** are described in the Nokia Qt GPL Exception version 1.3, included in
 ** the file GPL_EXCEPTION.txt in this package.
 **
 ** Qt for Windows(R) Licensees
 ** As a special exception, Nokia, as the sole copyright holder for Qt
 ** Designer, grants users of the Qt/Eclipse Integration plug-in the
 ** right for the Qt/Eclipse Integration to link to functionality
 ** provided by Qt Designer and its related libraries.
 **
 ** If you are unsure which license is appropriate for your use, please
 ** contact the sales department at qt-sales@nokia.com.
 **
 ** WARNING:
 **      A separate license from Unisys may be required to use the gif
 **      reader. See http://www.unisys.com/about__unisys/lzw/
 **      for information from Unisys
 **
 ****************************************************************************/

#include "fqtgahandler.h"

#include <qimage.h>
#include <qiodevice.h>
#include <qvariant.h>

#include <QtDebug>
QT_BEGIN_NAMESPACE

struct TGAHeader {
	unsigned char	IdLength;
	unsigned char	ColorMap;
	unsigned char	DataType;
	unsigned char	ColorMapInfo[5];
	unsigned char	X_Y_Origin[4];
	unsigned short	Width;
	unsigned short  Height;
	unsigned char	Bpp;
};

FQTGAHandler::FQTGAHandler()
{
}

FQTGAHandler::~FQTGAHandler()
{
}


bool FQTGAHandler::canRead() const
{
	if(device()->isReadable())
	{
		QByteArray arr = device()->peek(3);
		if((arr.at(2) == 2) || (arr.at(2) == 10))
		{
			return true;
		}
	}
	return false;
	
}

bool FQTGAHandler::canRead(QIODevice *device)
{
	if(device->isReadable())
	{
		QByteArray arr = device->peek(3);
		if((arr.at(2) == 2) || (arr.at(2) == 10))
		{
			qDebug("Supported format");
			return true;
		}
	}
	qDebug("Unsupported format");
	return false;
	
}

bool FQTGAHandler::read(QImage *image)
{
	//First of all read header
	TGAHeader	head;
	device()->read(reinterpret_cast<char*> (&head),sizeof(TGAHeader));
	//Skip desired bytes
	device()->seek(device()->pos()+head.IdLength);
	//Parse format and setup QImage
	QImage*	img;
	if(head.Bpp == 24)
		img = new QImage(head.Width,head.Height,QImage::Format_RGB32);
	else if(head.Bpp == 32)
		img = new QImage(head.Height,head.Width,QImage::Format_ARGB32);
	else
		return false; //Image is of unsopported format
	unsigned	BPP = head.Bpp >> 3;
	unsigned char rgb[4];
	QRgb val;
	unsigned int n = 0;//Number of processed pixel
	if(head.DataType == 2)
	{
		//Read block data
		while(n < static_cast<unsigned>(head.Width*head.Height))
		{
			
			device()->read(reinterpret_cast<char*>(rgb),BPP);
			
			if(BPP == 3)
			{
				val = qRgb(rgb[2],rgb[1],rgb[0]);			
			}
			else
			{
				val = qRgba(rgb[2],rgb[1],rgb[0],rgb[3]);
			}
			
			img->setPixel(n % head.Width,n / head.Width,val);
			n++;
		}
		
	}
	else if(head.DataType == 10)
	{
		while(n < static_cast<unsigned>(head.Width*head.Height))
		{
			unsigned char chunkHead;
			device()->read(reinterpret_cast<char*>(&chunkHead),1);
			bool isRLE = chunkHead & 128;
			unsigned numPix = (chunkHead & 127) + 1;
			
			if(isRLE)
			{
				device()->read(reinterpret_cast<char*>(rgb),BPP);
				
				if(BPP == 3)
				{
					val = qRgb(rgb[2],rgb[1],rgb[0]);			
				}
				else
				{
					val = qRgba(rgb[2],rgb[1],rgb[0],rgb[3]);
				}
				for(unsigned i = 0; i< numPix; i++) //Fill with pixels
				{
					img->setPixel(n % head.Width,n / head.Width,val);
					n++;
				}
			}
			else	//No rle compression
			{
				for(unsigned i = 0; i< numPix; i++) //Fill with pixels
				{
					device()->read(reinterpret_cast<char*>(rgb),BPP);
					
					if(BPP == 3)
					{
						val = qRgb(rgb[2],rgb[1],rgb[0]);			
					}
					else
					{
						val = qRgba(rgb[2],rgb[1],rgb[0],rgb[3]);
					}
					
					img->setPixel(n % head.Width,n / head.Width,val);
					n++;
				}
				
			}
		}
	}
	*image = *img;
	return true;
}

bool FQTGAHandler::write(const QImage &image)
{
	//Writing is available only to uncompressed format
	//First, create header
	TGAHeader	head;
	memset(&head,0,sizeof(TGAHeader));
	head.Width = image.width();
	head.Height = image.height();
	head.DataType = 2;
	if(image.format() == QImage::Format_RGB32)
        {
		head.Bpp = 24;
        }
        else if((image.format() == QImage::Format_ARGB32) || (image.format() == QImage::Format_ARGB32_Premultiplied))
        {
		head.Bpp = 32;
        }
	else return false;
		
	device()->write(reinterpret_cast<char*> (&head),sizeof(head));
	if(image.format() == QImage::Format_RGB32)
	{
		for(unsigned j = head.Height - 1; j < head.Height; j--)
			for(unsigned i = 0; i < head.Width; i++)
			{
				QRgb val = image.pixel(i,j);
				char bgr[3] = {qBlue(val),qGreen(val),qRed(val)};
				device()->write(bgr,3);
			}
	}
        else if((image.format() == QImage::Format_ARGB32) || (image.format() == QImage::Format_ARGB32_Premultiplied))
	{
		for(unsigned j = head.Height - 1; j < head.Height; j--)
			for(unsigned i = 0; i < head.Width; i++)
			{
				QRgb val = image.pixel(i,j);
				char bgra[4] = {qBlue(val),qGreen(val),qRed(val),qAlpha(val)};
				device()->write(bgra,4);
			}
	}
	else return false;
	return true;
}

bool FQTGAHandler::supportsOption(ImageOption option) const
{
	if(option == FQTGAHandler::Size) return true;
	return false;
}

QVariant FQTGAHandler::option(ImageOption option) const
{
	if(option == FQTGAHandler::Size)
	{
		TGAHeader head;
		device()->peek(reinterpret_cast<char*>(&head),sizeof(TGAHeader));
		return QSize(head.Width,head.Height);
	}
	return QVariant();
}



QT_END_NAMESPACE
