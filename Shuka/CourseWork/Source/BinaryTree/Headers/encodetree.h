#ifndef ENCODETREE_H
#define ENCODETREE_H

#include <QMap>
#include <QString>
#include <QVector>


struct Symbol
{
    /*
     * Structure for storing a symbol and it's "weight".
    */

    QChar data_;
    size_t weight_;

    Symbol (const Symbol& data) : data_(data.data_),
        weight_(data.weight_) { }

    Symbol (QChar data = 0, size_t weight = 0) :
        data_(data), weight_(weight) { }
};


class EncodeTree
{
    /*
     * Base abstract tree class that implements methods for working with
     * binary coding tree.
    */

public:
    explicit EncodeTree();

    explicit EncodeTree (const Symbol& data);

    virtual ~EncodeTree();

    EncodeTree (const EncodeTree& tree);

    EncodeTree& operator= (const EncodeTree& tree);

    EncodeTree (const EncodeTree&& tree) = delete;

    EncodeTree& operator= (const EncodeTree&& tree) = delete;

    const EncodeTree* getLeft() const;

    const EncodeTree* getRight() const;

    const EncodeTree* getParent() const;

    const Symbol* getData() const;

    size_t getHeight() const;

    bool isEmptyNode() const;

    bool isLeaf() const;

    void setLeft (EncodeTree* left);

    void setRight (EncodeTree* right);

    void setParent (EncodeTree* parent);

    void setData (const Symbol& data);

    void concatenateTrees (size_t weight, EncodeTree* left, EncodeTree* right);

    QString encodeText (const QString& text);

    QMap<QString, QChar> getCharactersCode() const;

    QString printTree() const;

protected:
    virtual void createEncodeTree (const QString& text) = 0;

    virtual EncodeTree* copyNode() const = 0;

    const EncodeTree* findSymbol (QChar data) const;

    void getCharactersCode (QMap<QString, QChar>& charactersCode,
                            const QString& path) const;

    void printTree (QString& result, size_t depth = 1) const;

private:
    Symbol* data_;
    EncodeTree* parent_;
    EncodeTree* left_;
    EncodeTree* right_;
};


#endif // ENCODETREE_H
