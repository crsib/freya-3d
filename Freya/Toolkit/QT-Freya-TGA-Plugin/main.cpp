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
****************************************************************************/

#include <qimageiohandler.h>
#include <qstringlist.h>
#include "fqtgahandler.h"

QT_BEGIN_NAMESPACE

class FQTGAPlugin : public QImageIOPlugin
{
public:
    FQTGAPlugin();
    ~FQTGAPlugin();

    QStringList keys() const;
    Capabilities capabilities(QIODevice *device, const QByteArray &format) const;
    QImageIOHandler *create(QIODevice *device, const QByteArray &format = QByteArray()) const;
};

FQTGAPlugin::FQTGAPlugin()
{
}

FQTGAPlugin::~FQTGAPlugin()
{
}

QStringList FQTGAPlugin::keys() const
{
    return QStringList() << QLatin1String("tga") << QLatin1String("TGA");
}

QImageIOPlugin::Capabilities FQTGAPlugin::capabilities(QIODevice *device, const QByteArray &format) const
{
        if((format == "tga") || format == "TGA")
		return Capabilities(CanRead | CanWrite);
	if(!format.isEmpty())
		return 0;
	if(!device->isOpen())
		return 0;
	Capabilities caps;
	if(device->isReadable() && FQTGAHandler::canRead(device))
		caps |= CanRead;
	if(device->isWritable())
		caps |= CanWrite;
	return caps;
}

QImageIOHandler *FQTGAPlugin::create(QIODevice *device, const QByteArray &format) const
{
    QImageIOHandler *handler = new FQTGAHandler;
    handler->setDevice(device);
    handler->setFormat(format);
    return handler;
}

Q_EXPORT_PLUGIN2(qftga, FQTGAPlugin)

QT_END_NAMESPACE
