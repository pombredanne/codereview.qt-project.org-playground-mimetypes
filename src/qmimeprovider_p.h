/**************************************************************************
**
** This file is part of QMime
**
** Based on Qt Creator source code
**
** Qt Creator Copyright (c) 2011 Nokia Corporation and/or its subsidiary(-ies).
**
**
** GNU Lesser General Public License Usage
**
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this file.
** Please review the following information to ensure the GNU Lesser General
** Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
**************************************************************************/

#ifndef QMIMEPROVIDER_P_H
#define QMIMEPROVIDER_P_H

#include "qmimedatabase_p.h"

class QMimeProviderBase
{
public:
    QMimeProviderBase(QMimeDatabasePrivate *db);
    virtual ~QMimeProviderBase() {}

    virtual bool isValid() = 0;
    virtual void ensureTypesLoaded() = 0;
    virtual QStringList findByName(const QString &fileName, QString *foundSuffix) = 0;
    virtual void ensureMagicLoaded() = 0;

    QMimeDatabasePrivate* m_db;
};

/*
   Parses mime.cache on demand
 */
class QMimeBinaryProvider : public QMimeProviderBase
{
public:
    QMimeBinaryProvider(QMimeDatabasePrivate *db);
    virtual ~QMimeBinaryProvider();

    virtual bool isValid();
    virtual void ensureTypesLoaded();
    virtual QStringList findByName(const QString &fileName, QString *foundSuffix);
    virtual void ensureMagicLoaded();

private:
    struct CacheFile;

    struct GlobMatchResult
    {
        void addMatch(const QString& mimeType, int weight, const QString &pattern);
        QStringList m_matchingMimeTypes;
        int m_weight;
        int m_matchingPatternLength;
        QString m_foundSuffix;
    };

    void matchGlobList(GlobMatchResult& result, CacheFile *cacheFile, int offset, const QString &fileName);
    bool matchSuffixTree(GlobMatchResult& result, CacheFile *cacheFile, int numEntries, int firstOffset, const QString &fileName, int charPos);

    QList<CacheFile *> m_cacheFiles;
};

/*
   Parses the raw XML files (slower)
 */
class QMimeXMLProvider : public QMimeProviderBase
{
public:
    QMimeXMLProvider(QMimeDatabasePrivate *db);

    virtual bool isValid();
    virtual void ensureTypesLoaded();
    virtual QStringList findByName(const QString &fileName, QString *foundSuffix);
    virtual void ensureMagicLoaded();

    bool load(const QString &fileName, QString *errorMessage);

    // Called by the mimetype xml parser
    bool addMimeType(const QMimeType &mt);
    void addGlobPattern(const QMimeGlobPattern& glob);

private:
    void ensureLoaded();
    void load(const QString &fileName);

    bool m_loaded;

    QMimeAllGlobPatterns m_mimeTypeGlobs;
};

#endif // QMIMEPROVIDER_P_H
