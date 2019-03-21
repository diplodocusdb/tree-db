/*
    Copyright (c) 2018-2019 Xavier Leclercq

    Permission is hereby granted, free of charge, to any person obtaining a
    copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
    IN THE SOFTWARE.
*/

#ifndef _DIPLODOCUSDB_TREEDB_CORE_TREEDBNODE_H_
#define _DIPLODOCUSDB_TREEDB_CORE_TREEDBNODE_H_

#include "TreeDBKey.h"
#include "TreeDBValue.h"
#include "Ishiko/Errors/Error.h"
#include <vector>
#include <memory>

namespace DiplodocusDB
{

class TreeDBNodeImpl;

class TreeDBNode
{
public:
    TreeDBNode();
    TreeDBNode(std::shared_ptr<TreeDBNodeImpl> impl);
    ~TreeDBNode();

    explicit operator bool() const;
    bool operator !() const;
    bool operator ==(const TreeDBNode& other) const;
    bool operator !=(const TreeDBNode& other) const;

    const TreeDBKey& key() const;
    const TreeDBValue& value() const;
    TreeDBValue& value();

    bool isRoot() const;
    TreeDBNode parent(Ishiko::Error& error);
    void children(std::vector<TreeDBNode>& children, Ishiko::Error& error);
    TreeDBNode child(const TreeDBKey& key, Ishiko::Error& error);
    TreeDBNode previousSibling(Ishiko::Error& error);
    TreeDBNode previousSibling(const TreeDBKey& key, Ishiko::Error& error);
    TreeDBNode nextSibling(Ishiko::Error& error);
    TreeDBNode nextSibling(const TreeDBKey& key, Ishiko::Error& error);

    TreeDBNode append(const TreeDBKey& key);
    TreeDBNode set(const TreeDBKey& key, Ishiko::Error& error);
    bool remove(const TreeDBKey& key, Ishiko::Error& error);
    void removeAll(Ishiko::Error& error);

    std::shared_ptr<TreeDBNodeImpl>& impl();

private:
    std::shared_ptr<TreeDBNodeImpl> m_impl;
};

}

#include "linkoptions.h"

#endif
