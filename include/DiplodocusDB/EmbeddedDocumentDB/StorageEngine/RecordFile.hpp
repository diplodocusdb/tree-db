/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/diplodocusdb/physical-storage/blob/main/LICENSE.txt
*/

#ifndef GUARD_DIPLODOCUSDB_EMBEDDEDDOCUMENTDB_STORAGEENGINE_RECORDFILE_HPP
#define GUARD_DIPLODOCUSDB_EMBEDDEDDOCUMENTDB_STORAGEENGINE_RECORDFILE_HPP

#include "RecordRepository.hpp"
#include "RecordRepositoryReader.hpp"
#include "RecordRepositoryWriter.hpp"
#include <DiplodocusDB/PhysicalStorage.hpp>
#include <boost/filesystem.hpp>
#include <Ishiko/Errors.hpp>
#include <memory>

namespace DiplodocusDB
{
namespace EDDBImpl
{

class RecordFile : public RecordRepository
{
public:
    void create(const boost::filesystem::path& path, Ishiko::Error& error);
    void open(const boost::filesystem::path& path, Ishiko::Error& error);
    void close();

    size_t pageCount();
    std::shared_ptr<PhysicalStorage::Page2> page(size_t index, Ishiko::Error& error) override;
    std::shared_ptr<PhysicalStorage::Page2> allocatePage(Ishiko::Error& error);
    std::shared_ptr<PhysicalStorage::Page2> insertPageAfter(PhysicalStorage::Page2& page,
        Ishiko::Error& error) override;
    void store(const PhysicalStorage::Page2& page, Ishiko::Error& error) override;

    RecordRepositoryReader read(const PhysicalStorage::PageRepositoryPosition& pos, Ishiko::Error& error);
    RecordRepositoryReader read(size_t startPage, size_t offset, Ishiko::Error& error);
    RecordRepositoryReader read(std::shared_ptr<PhysicalStorage::Page2> startPage, size_t offset,
        Ishiko::Error& error);

    RecordRepositoryWriter insert(const PhysicalStorage::PageRepositoryPosition& pos, Ishiko::Error& error);
    RecordRepositoryWriter insert(size_t startPage, size_t offset, Ishiko::Error& error);
    RecordRepositoryWriter insert(std::shared_ptr<PhysicalStorage::Page2> startPage, size_t offset,
        Ishiko::Error& error);

private:
    PhysicalStorage::PageFileRepository m_page_file_repository;
};

}
}

#endif
