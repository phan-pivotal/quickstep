// Copyright (c) 2014-2015, Quickstep Technologies LLC. All Rights Reserved.

#ifndef TMB_CANCELLATION_TOKEN_H_
#define TMB_CANCELLATION_TOKEN_H_

#include <cstdint>
#include <memory>

#include "tmb/internal/memory_mirror_cancellation_set.h"
#include "tmb/internal/shared_bool.h"

namespace tmb {

template <bool> class MemoryMirrorMessageBus;
template <bool> class PureMemoryMessageBus;

namespace internal {
template <bool, bool> class MemoryBasedMessageBus;
class NativeTransactionLog;
class NetMemoryContainerPusher;
class NetServiceImpl;
}  // namespace internal

/** \addtogroup TMB
 *  @{
 */

/**
 * @brief An opaque, copyable token that allows a sender to cancel a message
 *        which it previously sent.
 **/
class CancellationToken {
 public:
  CancellationToken()
      : message_id_(-1) {
  }

  CancellationToken(const CancellationToken &orig) = default;
  CancellationToken(
      CancellationToken &&orig) = default;  // NOLINT(build/c++11)

  CancellationToken& operator=(const CancellationToken &orig) = default;
  CancellationToken& operator=(
      CancellationToken &&orig) = default;  // NOLINT(build/c++11)

 private:
  friend class LevelDBMessageBus;
  friend class MemoryMirrorMessageBus<false>;
  friend class MemoryMirrorMessageBus<true>;
  friend class NativeNetClientMessageBus;
  friend class PureMemoryMessageBus<false>;
  friend class PureMemoryMessageBus<true>;
  friend class SQLiteMessageBus;
  friend class VoltDBMessageBus;
  friend class ZookeeperMessageBus;
  friend class internal::MemoryBasedMessageBus<false, false>;
  friend class internal::MemoryBasedMessageBus<false, true>;
  friend class internal::MemoryBasedMessageBus<true, false>;
  friend class internal::MemoryBasedMessageBus<true, true>;
  friend class internal::NativeTransactionLog;
  friend class internal::NetMemoryContainerPusher;
  friend class internal::NetServiceImpl;

  mutable internal::SharedBool in_memory_cancel_flag_;
  std::shared_ptr<internal::MemoryMirrorCancellationSet>
      memory_mirror_cancellation_set_;
  std::int64_t message_id_;
};

/** @} */

}  // namespace tmb

#endif  // TMB_CANCELLATION_TOKEN_H_
