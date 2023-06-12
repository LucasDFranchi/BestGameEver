#include <memory>
#include <stdio.h>

/**
 * @brief Class that implements a rotatory buffer
 *
 * @tparam T Generic parameter type
 */
template <class T> class FIFO {
private:
  std::unique_ptr<T[]> array; ///< Template array that stores the data.
  size_t _maximumSize;        ///< Maximum size of FIFO buffer.
  size_t _front_index;        ///< Index of the first item on the FIFO buffer.
  size_t _rear_index;         ///< Index of the last item on FIFO buffer.
  bool _flow; ///< Flag that indicates the last operation, true for push false
              ///< for pop.
public:
  FIFO(size_t maximumSize) {
    // array = std::make_unique<T[]>(maximumSize);
    array.reset(new T[maximumSize]);
    this->_maximumSize = maximumSize;
    this->_front_index = 0;
    this->_rear_index = 0;
    this->_flow = false;
  };
  ~FIFO(){};

  T Pop(void);
  bool Push(T &data);
  bool full(void) const &;
  bool empty(void) const &;
  T front(void) const &;
  T rear(void) const &;
};

/**
 * @brief Check if the FIFO is full.
 *
 * @tparam T Generic parameter type
 * @return true if the FIFO buffer is full.
 * @return false if the size of the FIFO buffer is smaller than maximum size.
 */
template <class T> bool FIFO<T>::full(void) const & {
  bool ret = false;

  if (this->_rear_index == this->_front_index) {
    if (this->_flow) {
      ret = true;
    }
  }
  return ret;
}
/**
 * @brief Check if the FIFO is empty.
 *
 * @tparam T Generic parameter type.
 * @return true if the FIFO buffer is empty.
 * @return false if the size of the FIFO buffer is greater than zero.
 */
template <class T> bool FIFO<T>::empty(void) const & {
  bool ret = false;

  if (this->_rear_index == this->_front_index) {
    if (!this->_flow) {
      ret = true;
    }
  }
  return ret;
}
/**
 * @brief Get the data from front.
 *
 * @tparam T Generic parameter type
 * @return Returns the data stored on front position, if the FIFO is empty
 * returns zero.
 */
template <class T> T FIFO<T>::front(void) const & {
  if (this->empty())
    return T();
  return this->array.get()[this->_front_index];
}
/**
 * @brief Get the data from rear.
 *
 * @tparam T Generic parameter type
 * @return Returns the data stored on front position, if the FIFO is empty
 * returns zero.
 */
template <class T> T FIFO<T>::rear(void) const & {
  T ret = T();
  if (!this->empty()) {
    ret = this->array.get()[this->_rear_index];
  }

  return ret;
}
/**
 * @brief Push a new generic data to the FIFO.
 *
 * @tparam T Generic parameter type.
 * @param data Generic item that should be added to the FIFO.
 * @return true if the FIFO is not full and the data was stored correctly.
 * @return false if the FIFO is full.
 */
template <class T> bool FIFO<T>::Push(T &data) {
  auto ret = false;
  if (!this->full()) {
    this->_flow = true;
    this->array.get()[this->_rear_index] = data;
    this->_rear_index = ((this->_rear_index + 1) % this->_maximumSize);
    ret = true;
  }

  return ret;
}
/**
 * @brief Get the data from front and removed from the FIFO.
 *
 * @tparam T Generic parameter type.
 * @return Returns the data stored on front position, if the FIFO is empty
 * returns zero.
 */
template <class T> T FIFO<T>::Pop(void) {
  T ret = T();

  if (!this->empty()) {
    this->_flow = false;
    ret = this->array.get()[this->_front_index];
    this->_front_index = (this->_front_index + 1) % this->_maximumSize;
  }
  return ret;
}