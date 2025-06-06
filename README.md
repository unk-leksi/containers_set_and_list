# 📦 Container Library in C++

*A modular container library using object-oriented programming in C++*

---

## 📌 Project Overview

This project is a collaborative academic assignment focused on implementing various data containers using object-oriented design in C++. Each student was responsible for developing one container.

**Team size**: 5 students  
**My contribution**: `Set` and singly linked `List` containers

---

## 🎯 Project Goals

- ✅ Implement **one container** per student  
- ✅ Implement a **custom memory manager** derived from `MemoryManager`  
- ✅ Use the provided base classes `Container`, `AbstractSet`, and `AbstractList` (without modification)  
- ✅ Organize a class hierarchy shared within the group  
- ✅ Use the `Mem` class from `Mem.h` for memory allocation  
- ✅ Conduct **performance experiments** to evaluate memory and algorithm efficiency  

## 🧩 My Contributions

### ✅ Set Container
- Inherits from `AbstractSet`
- Stores unique elements only
- Supports `insert`, `remove`, and `search` operations

### ✅ Singly Linked List Container
- Inherits from `AbstractList`
- Maintains sequential element order
- Supports dynamic insertion and traversal

---

## 🚀 Implemented Features

| Feature                          | Set | List |
|----------------------------------|:---:|:----:|
| Insert elements                  | ✅  | ✅   |
| Remove elements                  | ✅  | ✅   |
| Prevent duplicates               | ✅  | ➖   |
| Sequential traversal             | ➖  | ✅   |
| Custom memory management         | ✅  | ✅   |
| Derived from abstract interfaces | ✅  | ✅   |

---

## 🧪 Experimental Evaluation

- Measured runtime and memory usage for key operations
- Compared efficiency using built-in `new` vs custom `MemoryManager`
- Results provide insight into container performance and memory optimization potential

