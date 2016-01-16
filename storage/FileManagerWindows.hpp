/**
 * This file copyright (c) 2011-2015, Quickstep Technologies LLC.
 * All rights reserved.
 * See file CREDITS.txt for details.
 **/

#ifndef QUICKSTEP_STORAGE_FILE_MANAGER_WINDOWS_HPP_
#define QUICKSTEP_STORAGE_FILE_MANAGER_WINDOWS_HPP_

#include <cstddef>
#include <string>

#include "storage/FileManager.hpp"
#include "storage/StorageBlockInfo.hpp"
#include "utility/Macros.hpp"

namespace quickstep {

/** \addtogroup Storage
 *  @{
 */

/**
 * @brief An implementation of FileManager for Windows.
 **/
class FileManagerWindows : public FileManager {
 public:
  explicit FileManagerWindows(const std::string &storage_path)
      : FileManager(storage_path) { }

  ~FileManagerWindows() override { }

  bool deleteBlockOrBlob(const block_id block) override;

  bool readBlockOrBlob(const block_id block, void *buffer, const std::size_t length) override;

  bool writeBlockOrBlob(const block_id block, const void *buffer, const std::size_t length) override;

  std::size_t numSlots(const block_id block) const override;

  block_id_counter getMaxUsedBlockCounter(const block_id_domain block_domain) const override;

 private:
  DISALLOW_COPY_AND_ASSIGN(FileManagerWindows);
};

/** @} */

}  // namespace quickstep

#endif  // QUICKSTEP_STORAGE_FILE_MANAGER_WINDOWS_HPP_
