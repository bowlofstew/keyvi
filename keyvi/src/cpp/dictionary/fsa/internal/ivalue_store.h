/* * keyvi - A key value store.
 *
 * Copyright 2015 Hendrik Muhs<hendrik.muhs@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*
 * ivalue_store.h
 *
 *  Created on: Jun 12, 2014
 *      Author: hendrik
 */

#ifndef IVALUE_STORE_H_
#define IVALUE_STORE_H_

#include <boost/filesystem.hpp>
#include <boost/interprocess/file_mapping.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/container/flat_map.hpp>
#include <boost/variant.hpp>

namespace keyvi {
namespace dictionary {
namespace fsa {
namespace internal {

/**
 * "Registry" for value stores, required to differ between the stores.
 *
 * Do not forget to add the new value store to ValueStoreFactory
 */
enum value_store_t {
  NULL_VALUE_STORE = 1,  //!< NullValueStore
  INT_VALUE_STORE = 2,  //!< IntValueStore
  STRING_VALUE_STORE = 3, //!< StringValueStore
  JSON_VALUE_STORE = 4, // !< JsonValueStore
};

/* Writing value stores is based on template (duck-typing).
 *
 * The following types/constants/methods are required:
 *
 * typedef {type} value_t;
 * static const {type} no_value = 0;
 *
 * uint64_t GetValue(value_t value)
 *
 * value_store_t GetValueStoreType
 *
 * void Write(std::ostream& stream)
 */
class IValueStoreWriter {
};

/**
 * Base class / Interface definition for reading from the value store.
 *
 * Each ValueStore Reader implementation should inherit this interface.
 *
 * In addition
 */
class IValueStoreReader {
 public:
  typedef boost::container::flat_map<std::string, boost::variant<std::string, int, double, bool>> attributes_raw_t;
  typedef std::shared_ptr<attributes_raw_t> attributes_t;

  /**
   * Default constructor. Override if the value store implementation requires extra data.
   *
   * @param stream The stream to read from
   * @param file_mapping The file_mapping instance of the loader to use memory mapping
   */
  IValueStoreReader(std::istream& stream,
                    boost::interprocess::file_mapping* file_mapping) {
  }

  virtual ~IValueStoreReader() {
  }

  /**
   * Generic value format.
   *
   * @param fsa_value numeric value
   * @return The value in form of attributes
   */
  virtual attributes_t GetValueAsAttributeVector(uint64_t fsa_value) = 0;

  /**
   * Get Value as string in raw format
   *
   * @param fsa_value
   * @return the value as string without any decompression
   */
  virtual std::string GetRawValueAsString(uint64_t fsa_value) {
    return GetValueAsString(fsa_value);
  }

  /**
   * Get Value as string (for dumping or communication)
   *
   * @param fsa_value
   * @return the value as string
   */
  virtual std::string GetValueAsString(uint64_t fsa_value) = 0;

  /**
   * Get statistical information about the storage.
   */

  virtual std::string GetStatistics() const {
    return "";
  }
};

} /* namespace internal */
} /* namespace fsa */
} /* namespace dictionary */
} /* namespace keyvi */

#endif /* IVALUE_STORE_H_ */
