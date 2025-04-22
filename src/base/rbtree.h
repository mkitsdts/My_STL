#pragma once

#include <stdexcept>

constexpr auto RED = true;
constexpr auto BLACK = false;

namespace STL {
template <class value_type> struct RBTree {

  struct node {
  public:
    node(const value_type &value)
        : parent(nullptr), left(nullptr), right(nullptr), data(value),
          color(BLACK) {}
    node(node *parent_value, const value_type &value)
        : parent(parent_value), left(nullptr), right(nullptr), data(value),
          color(RED) {}
    ~node() {
      free(left);
      free(right);
      free(parent);
    }
    bool operator==(const node &value) {
      if ((data == value.data) && (left == value.left) &&
          (right == value.right) && (parent == value.parent) &&
          (color == value.color)) {
        return true;
      }
      return false;
    }
    bool operator!=(const node &value) { return !(*this == value); }
    bool operator<(const node &value) { return data < value.data; }
    bool operator>(const node &value) { return data > value.data; }
    bool color;
    node *left;
    node *right;
    node *parent;
    value_type data;
  };

  struct RBTreeIterator {
    RBTreeIterator(node *n) : _node(n) {}
    value_type operator*() {
      if (_node == nullptr) {
        throw std::out_of_range("Iterator out of range");
      }
      return _node->data;
    }
    RBTreeIterator operator++() {
      if (!_node)
        return *this;
      if (_node->right) {
        _node = _node->right;
        while (_node->left) {
          _node = _node->left;
        }
      } else {
        node *parent = _node->parent;
        while (parent && _node == parent->right) {
          _node = parent;
          parent = parent->parent;
        }
        _node = parent;
      }
      return *this;
    }
    RBTreeIterator operator++(int) {
      RBTreeIterator tmp = *this;
      ++(*this);
      return tmp;
    }
    bool operator!=(RBTreeIterator iter) {
      if (_node != iter._node) {
        return true;
      }
      return false;
    }
    bool operator==(RBTreeIterator iter) { return !(*this != iter); }

  private:
    node *_node;
  };

public:
  RBTree() : root(nullptr), size_(0) {}

  ~RBTree() {}

  void insert(const value_type &value) {
    if (root == nullptr) {
      root = new node(value);
    }
    node *cur = root;
    node *cur_parent = nullptr;
    while (cur) {
      if (value < cur->data) {
        cur_parent = cur;
        cur = cur->left;
      } else if (value > cur->data) {
        cur_parent = cur;
        cur = cur->right;
      } else {
        return;
      }
    }

    cur = new node(cur_parent, value);
    node *newnode = cur;
    if (value < cur_parent->data) {
      cur_parent->left = cur;
    } else {
      cur_parent->right = cur;
    }

    while (is_son_self_red(cur_parent)) {
      node *cur_grandfather = cur_parent->parent;
      if (cur_parent == cur_grandfather->left) {
        node *cur_uncle = cur_grandfather->right;
        if (cur_uncle && cur_uncle->color == RED) {
          cur_parent->color = BLACK;
          cur_uncle->color = BLACK;
          cur_grandfather->color = RED;

          cur = cur_grandfather;
          cur_parent = cur->parent;
        } else {
          if (cur == cur_parent->left) {
            right_rotate(cur_grandfather);
            cur_grandfather->color = RED;
            cur_parent->color = BLACK;
          } else // cur == parent->right
          {
            LR_rotate(cur_grandfather);
            cur_grandfather->color = RED;
            cur_parent->color = BLACK;
          }
          break;
        }
      } else {
        node *cur_uncle = cur_grandfather->left;
        if (cur_uncle && cur_uncle->color == RED) {
          cur_uncle->color = BLACK;
          cur_parent->color = BLACK;
          cur_grandfather->color = RED;
          cur = cur_grandfather;
          cur_parent = cur->parent;
        } else {
          if (cur == cur_parent->left) {
            RL_rotate(cur_grandfather);
            cur->color = BLACK;
            cur_grandfather->color = RED;
          } else // cur == parent->right
          {
            left_rotate(cur_grandfather);
            cur_grandfather->color = RED;
            cur_parent->color = BLACK;
          }
          break;
        }
      }
    }
    root->color = BLACK;
    ++size_;
  }

  bool erase(const value_type &value) {
    node *cur_parent = nullptr;
    node *cur = root;
    node *delParentPos = nullptr;
    node *delPos = nullptr;
    while (cur) {
      if (value < cur->data) {
        cur_parent = cur;
        cur = cur->left;
      } else if (value > cur->data) {
        cur_parent = cur;
        cur = cur->_right;
      } else {
        if (cur->left == nullptr) {
          if (cur == root) {
            root = root->right;
            if (root) {
              root->parent = nullptr;
              root->color = BLACK;
            }
            free(cur);
            return true;
          } else {
            delParentPos = cur_parent;
            delPos = cur;
          }
          break;
        } else if (cur->right == nullptr) {
          if (cur == root) {
            root = root->left;
            if (root) {
              root->parent = nullptr;
              root->color = BLACK;
            }
            free(cur);
            return true;
          } else {
            delParentPos = cur_parent;
            delPos = cur;
          }
          break;
        } else {
          node *minParent = cur;
          node *minRight = cur->right;
          while (minRight->left) {
            minParent = minRight;
            minRight = minRight->left;
          }
          cur->data = minRight->data;
          delParentPos = minParent;
          delPos = minRight;
          break;
        }
      }
    }
    if (delPos == nullptr) {
      return false;
    }

    node *del = delPos;
    node *delP = delParentPos;

    if (delPos->color == BLACK) {
      if (delPos->left) {
        delPos->left->color = BLACK;
      } else if (delPos->right) {
        delPos->right->color = BLACK;
      } else {
        while (delPos != root) {
          if (delPos == delParentPos->left) {
            node *brother = delParentPos->right;
            if (brother->color == RED) {
              delParentPos->color = RED;
              brother->color = BLACK;
              left_rotate(delParentPos);
              brother = delParentPos->right;
            }
            if (((brother->left == nullptr) ||
                 (brother->left->color == BLACK)) &&
                ((brother->right == nullptr) ||
                 (brother->right->color == BLACK))) {
              brother->color = RED;
              if (delParentPos->color == RED) {
                delParentPos->color = BLACK;
                break;
              }
              delPos = delParentPos;
              delParentPos = delPos->get_parent();
            } else {

              if ((brother->right == nullptr) ||
                  (brother->right->color == BLACK)) {
                brother->left->color = BLACK;
                brother->color = RED;
                right_rotate(brother);

                brother = delParentPos->right;
              }

              brother->colordelParentPos->color;
              delParentPos->color = BLACK;
              brother->right->color = BLACK;
              left_rotate(delParentPos);
              break;
            }
          } else // delPos == delParentPos->_right
          {
            node *brother = delParentPos->left;

            if (brother->color == RED) {
              delParentPos->color = RED;
              brother->color = BLACK;
              right_rotate(delParentPos);

              brother = delParentPos->left;
            }

            if (((brother->left == nullptr) ||
                 (brother->left->color == BLACK)) &&
                ((brother->right == nullptr) ||
                 (brother->right->color == BLACK))) {
              brother->color = RED;
              if (delParentPos->color == RED) {
                delParentPos->color = BLACK;
                break;
              }

              delPos = delParentPos;
              delParentPos = delPos->get_parent();
            } else {

              if ((brother->left == nullptr) ||
                  (brother->left->color == BLACK)) {
                brother->get_right->color = BLACK;
                brother->color = RED;
                left_rotate(brother);

                brother = delParentPos->left;
              }

              else if (!brother->color) {
                delParentPos->color = BLACK;
                brother->left->color = BLACK;
                right_rotate(delParentPos);
                break;
              }
            }
          }
        }
      }
    }

    if (del->left == nullptr) {
      if (del == delP->left) {
        delP->set_left(del->right);
        if (del->right)
          del->right->parent = delP;
      } else {
        delP->set_right(del->right);
        if (del->right)
          del->right->parent = delP;
      }
    } else {
      if (del == delP->left) {
        delP->set_left(del->left);
        if (del->left)
          del->left->parent = delP;
      } else {
        delP->set_right(del->left);
        if (del->left)
          del->left->parent = delP;
      }
    }
    free(del);
    --size_;
    return true;
  }

  void clear() {
    del(root);
    root = nullptr;
    size_ = 0;
  }

  bool empty() { return root == nullptr; }

  node *find(const value_type &value) {
    node *cur = root;
    while (cur) {
      if (value < cur->data) // keyֵС�ڸý���ֵ
      {
        cur = cur->left;            // �ڸý������������в���
      } else if (value > cur->data) // keyֵ���ڸý���ֵ
      {
        cur = cur->right; // �ڸý������������в���
      } else              // �ҵ���Ŀ����
      {
        return cur; // ���ظý��
      }
    }
    return nullptr; // ����ʧ��
  }

  unsigned int size() { return size_; }

  RBTreeIterator begin() {
    if (!root) {
      return RBTreeIterator(nullptr);
    }
    auto curr = root;
    while (curr->left) {
      curr = curr->left;
    }
    return RBTreeIterator(curr);
  }

  RBTreeIterator end() { return RBTreeIterator(nullptr); }

private:
  bool root_is_black() { return root->color == BLACK; }

  bool is_son_self_red(node *&insert) {
    if (insert == nullptr) {
      return false;
    }
    if (insert->color == RED) {
      if (insert->parent->color == RED) {
        return true;
      }
    }
    return false;
  }

  void del(node *&del) {
    if (del->left) {
      del(del->left);
    }
    if (del->right) {
      del(del->right);
    }
    free(del);
  }
  // ����
  void left_rotate(node *&cparent) {
    node *subR = cparent->right;
    node *subRL = subR->left;
    node *cparentParent = cparent->parent;
    // ����subRL��parent֮�����ϵ
    cparent->right = subRL;
    if (subRL)
      subRL->parent = cparent;

    // ����parent��subR֮�����ϵ
    subR->left = (cparent);
    cparent->parent = subR;

    // ����subR��parentParent֮�����ϵ
    if (cparentParent == nullptr) {
      root = subR;
      root->parent = nullptr;
    } else {
      if (cparent == cparentParent->left) {
        cparentParent->left = subR;
      } else {
        cparentParent->right = subR;
      }
      subR->parent = cparentParent;
    }
  }
  // ����
  void right_rotate(node *&cparent) {
    node *subL = cparent->left;
    node *subLR = subL->right;
    node *cparentParent = cparent->parent;

    // ����subLR��parent֮�����ϵ
    cparent->left = subLR;
    if (subLR)
      subLR->parent = cparent;

    // ����parent��subL֮�����ϵ
    subL->right = cparent;
    cparent->parent = subL;

    // ����subL��parentParent֮�����ϵ
    if (cparentParent == nullptr) {
      root = subL;
      root->parent = nullptr;
    } else {
      if (cparent == cparentParent->left) {
        cparentParent->left = subL;
      } else {
        cparentParent->right = subL;
      }
      subL->parent = cparentParent;
    }
  }

  // ����˫��
  void LR_rotate(node *&cparent) {
    left_rotate(cparent);
    right_rotate(cparent->left);
  }
  void RL_rotate(node *&cparent) {
    right_rotate(cparent);
    left_rotate(cparent->right);
  }

  void fixAfterInsert(node *cur) {
    // 如果是根节点，直接变黑
    if (cur == root) {
      cur->color = BLACK;
      return;
    }

    // 父节点为黑色，无需调整
    if (cur->parent->color == BLACK) {
      return;
    }

    // 父节点为红色时需要调整
    node *cur_parent = cur->parent;
    node *cur_grandfather = cur_parent->parent;

    // 父节点没有父节点(即父节点是根)，特殊情况
    if (!cur_grandfather) {
      cur_parent->color = BLACK;
      return;
    }

    // 根据父节点是祖父节点的左子节点还是右子节点分情况处理
    if (cur_parent == cur_grandfather->left) {
      node *cur_uncle = cur_grandfather->right;

      // 情况1: 叔叔节点也是红色
      if (cur_uncle && cur_uncle->color == RED) {
        cur_parent->color = BLACK;
        cur_uncle->color = BLACK;
        cur_grandfather->color = RED;
        fixAfterInsert(cur_grandfather); // 递归向上调整
      }
      // 情况2: 叔叔节点是黑色
      else {
        if (cur == cur_parent->right) { // LR情况
          // 先左旋父节点
          left_rotate(cur_parent);
          // 交换当前节点和父节点的引用
          node *temp = cur;
          cur = cur_parent;
          cur_parent = temp;
        }

        // LL情况: 右旋祖父节点
        right_rotate(cur_grandfather);
        // 调整颜色
        cur_parent->color = BLACK;
        cur_grandfather->color = RED;
      }
    } else { // 父节点是祖父节点的右子节点
      node *cur_uncle = cur_grandfather->left;

      // 情况1: 叔叔节点是红色
      if (cur_uncle && cur_uncle->color == RED) {
        cur_parent->color = BLACK;
        cur_uncle->color = BLACK;
        cur_grandfather->color = RED;
        fixAfterInsert(cur_grandfather); // 递归向上调整
      }
      // 情况2: 叔叔节点是黑色
      else {
        if (cur == cur_parent->left) { // RL情况
          // 先右旋父节点
          right_rotate(cur_parent);
          // 交换当前节点和父节点的引用
          node *temp = cur;
          cur = cur_parent;
          cur_parent = temp;
        }

        // RR情况: 左旋祖父节点
        left_rotate(cur_grandfather);
        // 调整颜色
        cur_parent->color = BLACK;
        cur_grandfather->color = RED;
      }
    }

    // 确保根节点为黑色
    root->color = BLACK;
  }

public:
  node *root;

private:
  unsigned int size_;
};

} // namespace STL