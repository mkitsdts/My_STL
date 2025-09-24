//
// Created by mkitsdts on 16/6/2024.
//

#pragma once

#include <cassert>
#include <cstddef>

constexpr auto ALIGN = 8;
constexpr auto MAX_BYTES = 128;
constexpr auto NFREELIST = 16;
constexpr auto NOBJS = 20;

namespace STL {
class Alloc {
private:
  union obj {
    union obj *free_list_link;
    char client_data[1];
  };
  inline static obj *free_list[NFREELIST] = {nullptr};

private:
  inline static char *start_free = nullptr;
  inline static char *end_free = nullptr;
  inline static std::size_t heap_size = 0;

private:
  static std::size_t ROUND_UP(std::size_t size) {
    return (size + ALIGN - 1) & ~(ALIGN - 1);
  }

  static std::size_t FREELIST_INDEX(std::size_t size) {
    return (((size) + ALIGN - 1) / ALIGN - 1);
  }

  static void *refill(std::size_t size) {
    std::size_t nobjs = NOBJS;
    void *chunk = chunk_alloc(size, nobjs);

    if (nobjs == 1) {
      return chunk;
    } else {
      obj **add_needed_free_list = free_list + FREELIST_INDEX(size);
      obj *result = (obj *)(chunk);
      obj *current_obj = nullptr;
      obj *next_obj = nullptr;

      *add_needed_free_list = (obj *)((obj *)chunk + size);
      next_obj = (obj *)((obj *)chunk + size);
      // added remaining memory blocks to the corresponding free list
      for (size_t i = 1;; ++i) {
        current_obj = next_obj;
        next_obj = (obj *)((char *)next_obj + size);
        if (nobjs - 1 == i) {
          current_obj->free_list_link = nullptr;
          break;
        } else {
          current_obj->free_list_link = next_obj;
        }
      }
      return result;
    }
  }

  // Apply for a chunk of memory from the heap
  // nobjs is a reference parameter, which may be modified
  static char *chunk_alloc(std::size_t size, std::size_t &nobjs) {
    char *result = nullptr;
    std::size_t total = size * nobjs;               // needed memory
    std::size_t bytes_left = end_free - start_free; // remaining memory

    if (bytes_left >= total) {
      // remaining memory is enough to meet the needs
      result = start_free;
      start_free = start_free + total;
      return result;
    } else if (bytes_left >= size) {
      // remaining memory is not enough to meet the needs, but can still
      // allocate one block modify nobjs's value to use the remaining memory
      nobjs = bytes_left / size;
      total = nobjs * size;
      result = start_free;
      start_free = start_free + total;
      return result;
    } else {
      // remaining memory is not enough to allocate one block
      std::size_t need_bytes = 2 * total + ROUND_UP(heap_size >> 4);
      if (bytes_left > 0) {
        // remaining memory can be used to establish a free list
        // the starting address of the free list is aligned
        obj **appropriate_free_list = free_list + FREELIST_INDEX(bytes_left);
        ((obj *)start_free)->free_list_link = *appropriate_free_list;
        *appropriate_free_list = (obj *)(start_free);
        // link the remaining memory block to the free list
      }
      // allocate memory
      start_free = static_cast<char *>(operator new(need_bytes));
      // allocation failed
      if (start_free == nullptr) {
        // remaining memory can be put into the free list
        obj **temp_free_list = nullptr;
        obj *temp = nullptr;
        for (size_t i = 0; i < NFREELIST; ++i) {
          temp_free_list = free_list + i;
          temp = *temp_free_list;
          if (temp != nullptr) {
            *temp_free_list = temp->free_list_link;
            start_free = (char *)temp;
            end_free = start_free + ALIGN * i;
            return chunk_alloc(size, nobjs);
          }
        }
        end_free = nullptr;
      }
      // allocation succeeded
      // remaining memory can be used to establish a free list
      heap_size += need_bytes;
      end_free = start_free + need_bytes;
      return chunk_alloc(size, nobjs);
    }
  }

public:
  // Allocate memory
  static void *allocate(std::size_t size) {
    // If size is greater than MAX_BYTES, use system malloc
    if (size > MAX_BYTES) {
      return operator new(size);
    }
    // index is the corresponding free_list node
    std::size_t index = FREELIST_INDEX(size);
    obj *list = free_list[index];
    if (list) {
      // list is not empty
      free_list[index] = list->free_list_link;
      return list;
    } else {
      // list is empty, need to allocate memory
      return refill(ROUND_UP(size));
    }
  }
  // Deallocate memory
  static void deallocate(void *ptr, std::size_t bytes) {
    if (bytes > MAX_BYTES) {
      operator delete(ptr);
    } else {
      std::size_t index = FREELIST_INDEX(bytes);
      obj *node = static_cast<obj *>(ptr);
      node->free_list_link = free_list[index];
      free_list[index] = node;
    }
  }
  // Reallocate memory
  static void *reallocate(void *&ptr, std::size_t old_sz, std::size_t new_sz) {
    deallocate(ptr, old_sz);
    ptr = allocate(new_sz);
    return ptr;
  }

public:
  Alloc() {
    start_free = nullptr;
    end_free = nullptr;
    heap_size = 0;
  };
  ~Alloc() = default;
};

} // namespace STL
