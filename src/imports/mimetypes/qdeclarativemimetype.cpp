/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the QtMimeTypes addon of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** Other Usage
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "qdeclarativemimetype_p.h"   // Basis

#include "qmimemagicrulematcher_p.h"

#include <QtCore/QDebug>
#include <qmimetype_p.h>

// ------------------------------------------------------------------------------------------------

/*!
    \qmlclass MimeType
    \brief File or data type, represented by a MIME type string
    \inherits QObject
 */

// ------------------------------------------------------------------------------------------------

QDeclarativeMimeType::QDeclarativeMimeType(QObject *theParent) :
        QObject(theParent),
        m_MimeType()
{}

// ------------------------------------------------------------------------------------------------

QDeclarativeMimeType::QDeclarativeMimeType(const QMimeType &other, QObject *theParent) :
        QObject(theParent),
        m_MimeType(other)
{
    //qDebug() << Q_FUNC_INFO << "name():" << name();
    ////qDebug() << Q_FUNC_INFO << "aliases():" << aliases();
    ////qDebug() << Q_FUNC_INFO << "comment():" << comment();
    //qDebug() << Q_FUNC_INFO << "genericIconName():" << genericIconName();
    //qDebug() << Q_FUNC_INFO << "iconName():" << iconName();
    //qDebug() << Q_FUNC_INFO << "globPatterns():" << globPatterns();
    //qDebug() << Q_FUNC_INFO << "suffixes():" << suffixes();
}

// ------------------------------------------------------------------------------------------------

#ifdef Q_COMPILER_RVALUE_REFS
QDeclarativeMimeType::QDeclarativeMimeType(QMimeType &&other, QObject *theParent) :
        QObject(theParent),
        m_MimeType(other)
{
    //qDebug() << Q_FUNC_INFO << "name():" << name();
    ////qDebug() << Q_FUNC_INFO << "aliases():" << aliases();
    ////qDebug() << Q_FUNC_INFO << "comment():" << comment();
    //qDebug() << Q_FUNC_INFO << "genericIconName():" << genericIconName();
    //qDebug() << Q_FUNC_INFO << "iconName():" << iconName();
    //qDebug() << Q_FUNC_INFO << "globPatterns():" << globPatterns();
    //qDebug() << Q_FUNC_INFO << "suffixes():" << suffixes();
}
#endif

// ------------------------------------------------------------------------------------------------

QDeclarativeMimeType::~QDeclarativeMimeType()
{
    //qDebug() << Q_FUNC_INFO << "name():" << name();
    ////qDebug() << Q_FUNC_INFO << "aliases():" << aliases();
    ////qDebug() << Q_FUNC_INFO << "comment():" << comment();
    //qDebug() << Q_FUNC_INFO << "genericIconName():" << genericIconName();
    //qDebug() << Q_FUNC_INFO << "iconName():" << iconName();
    //qDebug() << Q_FUNC_INFO << "globPatterns():" << globPatterns();
    //qDebug() << Q_FUNC_INFO << "suffixes():" << suffixes();
}

// ------------------------------------------------------------------------------------------------

/*!
    \qmlmethod MimeType::assign()
    Assigns from another object.
 */
void QDeclarativeMimeType::assign(QDeclarativeMimeType *other)
{
    if (other == 0) {
        qWarning() << Q_FUNC_INFO << "other is 0!";
        m_MimeType = QMimeType();
        return;
    }

    m_MimeType = other->m_MimeType;
}

// ------------------------------------------------------------------------------------------------

/*!
    \qmlmethod MimeType::equals()
    Compares with the other object for equality.
 */
bool QDeclarativeMimeType::equals(QDeclarativeMimeType *other) const
{
    if (other == 0) {
        qWarning() << Q_FUNC_INFO << "other is 0!";
        return false;
    }

    return this == other || m_MimeType == other->m_MimeType;
}

// ------------------------------------------------------------------------------------------------

#define ASSIGN_TO_PROPERTY(name) \
    result[#name] = name();

/*!
    \qmlmethod MimeType::properties()
    Returns the properties as a JavaScript object.
 */
QVariantMap QDeclarativeMimeType::properties() const
{
    QVariantMap result;
    ASSIGN_TO_PROPERTY(name)
    //ASSIGN_TO_PROPERTY(aliases)
    //ASSIGN_TO_PROPERTY(comment)
    ASSIGN_TO_PROPERTY(genericIconName)
    ASSIGN_TO_PROPERTY(iconName)
    ASSIGN_TO_PROPERTY(globPatterns)
    return result;
}

// ------------------------------------------------------------------------------------------------

#define ASSIGN_FROM_PROPERTY(name, setter, variantType, converter) \
    if (!other.contains(#name)) { \
        if (false) { \
            qDebug() << Q_FUNC_INFO << "Variant does not contain" << #name; \
        } \
    } \
    else if (other[#name].type() != QVariant::variantType) { \
        if (false) { \
            qDebug() << Q_FUNC_INFO << "Variant for" << #name << "has wrong type" << other[#name].type() << "with" << other[#name]; \
        } \
    } \
    else { \
        setter(other[#name].converter()); \
    }

/*!
    \qmlmethod MimeType::assignProperties()
    Assigns all properties from a JavaScript object.
 */
void QDeclarativeMimeType::assignProperties(const QVariantMap &other)
{
    m_MimeType = QMimeType(QMimeTypePrivate());
    ASSIGN_FROM_PROPERTY(name, setName, String, toString)
    //ASSIGN_FROM_PROPERTY(aliases, setAliases, List, toList)
    //ASSIGN_FROM_PROPERTY(comment, setComment, String, toString)
    ASSIGN_FROM_PROPERTY(genericIconName, setGenericIconName, String, toString)
    ASSIGN_FROM_PROPERTY(iconName, setIconName, String, toString)
    ASSIGN_FROM_PROPERTY(globPatterns, setGlobPatterns, List, toList)
}

// ------------------------------------------------------------------------------------------------

#define EQUALS_PROPERTY(name, variantType, converter) \
    if (!other.contains(#name)) { \
        if (false) { \
            qDebug() << Q_FUNC_INFO << "Variant does not contain" << #name << name(); \
        } \
        return false; \
    } \
    \
    if (other[#name].type() != QVariant::variantType) { \
        if (false) { \
            qDebug() << Q_FUNC_INFO << "Variant for" << #name << "has wrong type" << other[#name].type() << "for" << name() << "with" << other[#name]; \
        } \
        return false; \
    } \
    if (name() != other[#name].converter()) { \
        if (false) { \
            qDebug() << Q_FUNC_INFO << "Values for" << #name << "differ:" << name() << other[#name]; \
        } \
        return false; \
    }

/*!
    \qmlmethod MimeType::equalsProperties()
    Compares if the properties of the specified JavaScript object are equal.
 */
bool QDeclarativeMimeType::equalsProperties(const QVariantMap &other) const
{
    EQUALS_PROPERTY(name, String, toString)
    //EQUALS_PROPERTY(aliases, List, toList)
    //EQUALS_PROPERTY(comment, String, toString)
    EQUALS_PROPERTY(genericIconName, String, toString)
    EQUALS_PROPERTY(iconName, String, toString)
    EQUALS_PROPERTY(globPatterns, List, toList)

    return true;
}

// ------------------------------------------------------------------------------------------------

QMimeType QDeclarativeMimeType::mimeType() const
{
    return m_MimeType;
}

// ------------------------------------------------------------------------------------------------

bool QDeclarativeMimeType::isValid() const
{
    return m_MimeType.isValid();
}

// ------------------------------------------------------------------------------------------------

#ifndef Q_COMPILER_RVALUE_REFS
QMIMETYPE_BUILDER
#else
QMIMETYPE_BUILDER_FROM_RVALUE_REFS
#endif

// ------------------------------------------------------------------------------------------------

/*!
    \qmlproperty QString MimeType::name
    name of the MIME type
 */

// ------------------------------------------------------------------------------------------------

QString QDeclarativeMimeType::name() const
{
    return m_MimeType.name();
}

// ------------------------------------------------------------------------------------------------

void QDeclarativeMimeType::setName(const QString &newName)
{
#ifndef Q_COMPILER_RVALUE_REFS
    m_MimeType = buildQMimeType(newName, m_MimeType.genericIconName(), m_MimeType.iconName(), m_MimeType.globPatterns());
#else
    m_MimeType = buildQMimeType(QString(newName), m_MimeType.genericIconName(), m_MimeType.iconName(), m_MimeType.globPatterns());
#endif
}

// ------------------------------------------------------------------------------------------------

#if 0
QVariantList QDeclarativeMimeType::aliases() const
{
    QVariantList result;

    foreach (const QString &str, m_MimeType.aliases()) {
        result << str;
    }

    return result;
}

// ------------------------------------------------------------------------------------------------

void QDeclarativeMimeType::setAliases(const QVariantList &newAliases)
{
    QList<QString> newAliasesStringList;

    foreach (const QVariant &variant, newAliases) {
        if (variant.type() != QVariant::String) {
            qWarning() << Q_FUNC_INFO << "variant" << variant << "is not a string!";
            continue;
        }

        newAliasesStringList << variant.toString();
    }

#ifndef Q_COMPILER_RVALUE_REFS
    m_MimeType = buildQMimeType(m_MimeType.name(), newAliasesStringList, m_MimeType.comment(), m_MimeType.genericIconName(), m_MimeType.iconName(), m_MimeType.globPatterns());
#else
    m_MimeType = buildQMimeType(m_MimeType.name(), QVariantList(newAliasesStringList), m_MimeType.comment(), m_MimeType.genericIconName(), m_MimeType.iconName(), m_MimeType.globPatterns());
#endif
}

// ------------------------------------------------------------------------------------------------

QString QDeclarativeMimeType::comment() const
{
    return m_MimeType.comment();
}

// ------------------------------------------------------------------------------------------------

void QDeclarativeMimeType::setComment(const QString &newComment)
{
#ifndef Q_COMPILER_RVALUE_REFS
    m_MimeType = buildQMimeType(m_MimeType.name(), /*m_MimeType.aliases(),*/ newComment, m_MimeType.genericIconName(), m_MimeType.iconName(), m_MimeType.globPatterns());
#else
    m_MimeType = buildQMimeType(m_MimeType.name(), /*m_MimeType.aliases(),*/ QString(newComment), m_MimeType.genericIconName(), m_MimeType.iconName(), m_MimeType.globPatterns());
#endif
}

// ------------------------------------------------------------------------------------------------
#endif

/*!
    \qmlproperty QString MimeType::genericIconName
    file name of an icon image that represents the MIME type
 */

// ------------------------------------------------------------------------------------------------

QString QDeclarativeMimeType::genericIconName() const
{
    return m_MimeType.genericIconName();
}

// ------------------------------------------------------------------------------------------------

void QDeclarativeMimeType::setGenericIconName(const QString &newGenericIconName)
{
#ifndef Q_COMPILER_RVALUE_REFS
    m_MimeType = buildQMimeType(m_MimeType.name(), newGenericIconName, m_MimeType.iconName(), m_MimeType.globPatterns());
#else
    m_MimeType = buildQMimeType(m_MimeType.name(), QString(newGenericIconName), m_MimeType.iconName(), m_MimeType.globPatterns());
#endif
}

// ------------------------------------------------------------------------------------------------

/*!
    \qmlproperty QString MimeType::iconName
    file name of an icon image that represents the MIME type
 */

// ------------------------------------------------------------------------------------------------

QString QDeclarativeMimeType::iconName() const
{
    return m_MimeType.iconName();
}

// ------------------------------------------------------------------------------------------------

void QDeclarativeMimeType::setIconName(const QString &newIconName)
{
#ifndef Q_COMPILER_RVALUE_REFS
    m_MimeType = buildQMimeType(m_MimeType.name(), m_MimeType.genericIconName(), newIconName, m_MimeType.globPatterns());
#else
    m_MimeType = buildQMimeType(m_MimeType.name(), m_MimeType.genericIconName(), QString(newIconName), m_MimeType.globPatterns());
#endif
}

// ------------------------------------------------------------------------------------------------

QVariantList QDeclarativeMimeType::globPatterns() const
{
    QVariantList result;

    foreach (const QString &str, m_MimeType.globPatterns()) {
        result << str;
    }

    return result;
}

// ------------------------------------------------------------------------------------------------

void QDeclarativeMimeType::setGlobPatterns(const QVariantList &newGlobPatterns)
{
    QList<QString> newGlobPatternsStringList;

    foreach (const QVariant &variant, newGlobPatterns) {
        if (variant.type() != QVariant::String) {
            qWarning() << Q_FUNC_INFO << "variant" << variant << "is not a string!";
            continue;
        }

        newGlobPatternsStringList << variant.toString();
    }

#ifndef Q_COMPILER_RVALUE_REFS
    m_MimeType = buildQMimeType(m_MimeType.name(), m_MimeType.genericIconName(), m_MimeType.iconName(), newGlobPatternsStringList);
#else
    m_MimeType = buildQMimeType(m_MimeType.name(), m_MimeType.genericIconName(), m_MimeType.iconName(), QStringList(newGlobPatternsStringList));
#endif
}

// ------------------------------------------------------------------------------------------------

/*!
    \qmlproperty QVariantList MimeType::suffixes
    known suffixes for the MIME type
 */

// ------------------------------------------------------------------------------------------------

QVariantList QDeclarativeMimeType::suffixes() const
{
    QVariantList result;

    foreach (const QString &str, m_MimeType.suffixes()) {
        result << str;
    }

    return result;
}
