#pragma once
#ifndef MY_STL_RED_BLACK_TREE
#define MY_STL_RED_BLACK_TREE
#include "../allocator/Allocator.h"

constexpr auto RED = true;
constexpr auto BLACK = false;

namespace STL
{
	template <class value_type>
	struct RBTree
	{
		
		struct node
		{
		public:
			node(value_type& value) :parent(nullptr), left(nullptr), right(nullptr), data(value_type()), color(BLACK)//根节点
			{
			}
			node(node* parent_value, value_type& value) :parent(parent_value), left(nullptr), right(nullptr), data(value), color(RED)//普通节点
			{
			}
			~node()
			{
				free(left);
				free(right);
				free(parent);
			}
			bool operator == (const node& value)
			{
				if ((data == value.data) && (left == value.left) && (right == value.right) && (parent == value.parent) && (color == value.color))
				{
					return true;
				}
				return false;
			}
			bool operator != (const node& value)
			{
				return !(*this == value);
			}
			bool operator < (const node& value)
			{
				return data < value.data;
			}
			bool operator > (const node& value)
			{
				return data > value.data;
			}
			bool color;
			node* left;
			node* right;
			node* parent;
			value_type data;
		};
	public:
		RBTree() :root(nullptr)
		{
		}
		~RBTree()
		{
		}
		void insert(value_type& value)
		{
			if (root == nullptr) //若红黑树为空树，则插入结点直接作为根结点
			{
				root = new node(value);
			}
			//找到待插入位置
			node* cur = root;
			node* cur_parent = nullptr;
			while (cur)
			{
				if (value < cur->data)
				{
					cur_parent = cur;
					cur = cur->left;
				}
				else if (value > cur->data)
				{
					cur_parent = cur;
					cur = cur->right;
				}
				else
				{
					return;
				}
			}

			cur = new node(cur_parent,value); //根据所给值构造一个结点
			node* newnode = cur; //记录结点（便于后序返回
			if (value < cur_parent->data)
			{
				//插入到parent的左边
				cur_parent->left = cur;
			}
			else
			{
				//插入到parent的右边
				cur_parent->right = cur;
			}

			//对红黑树进行调整
			while (is_son_self_red(cur_parent))//父结点和待插入节点是红色
			{
				node* cur_grandfather = cur_parent->parent; //parent是红色，则其父结点一定存在
				if (cur_parent == cur_grandfather->left) //parent是grandfather的左孩子
				{
					node* cur_uncle = cur_grandfather->right; //uncle是grandfather的右孩子
					if (cur_uncle && cur_uncle->color == RED) //uncle存在且为红
					{
						//颜色调整
						cur_parent->color = BLACK;
						cur_uncle->color = BLACK;
						cur_grandfather->color = RED;

						//继续往上处理
						cur = cur_grandfather;
						cur_parent = cur->parent;
					}
					else //uncle为黑
					{
						//左左情况
						if (cur == cur_parent->left)
						{
							right_rotate(cur_grandfather); //右单旋
							//颜色调整
							cur_grandfather->color = RED;
							cur_parent->color = BLACK;
						}
						//左右情况
						else //cur == parent->right
						{
							LR_rotate(cur_grandfather); //左右双旋
							//颜色调整
							cur_grandfather->color = RED;
							cur_parent->color = BLACK;
						}
						break; //子树旋转后，该子树的根变成了黑色，无需继续往上进行处理
					}
				}
				else //parent是grandfather的右孩子
				{
					node* cur_uncle = cur_grandfather->left;
					if (cur_uncle && cur_uncle->color == RED)
					{
						//颜色调整
						cur_uncle->color = BLACK;
						cur_parent->color = BLACK;
						cur_grandfather->color = RED;
						//继续往上处理
						cur = cur_grandfather;
						cur_parent = cur->parent;
					}
					else
					{
						//右左情况
						if (cur == cur_parent->left)
						{
							RL_rotate(cur_grandfather); //右左双旋

							//颜色调整
							cur->color = BLACK;
							cur_grandfather->color = RED;
						}
						//右右情况
						else //cur == parent->right
						{
							left_rotate(cur_grandfather); //左单旋
							//颜色调整
							cur_grandfather->color = RED;
							cur_parent->color = BLACK;
						}
						break; //子树旋转后，该子树的根变成了黑色，无需继续往上进行处理
					}
				}
			}
			root->color = BLACK; //根结点的颜色为黑色（可能被情况一变成了红色，需要变回黑色）
		}
		void insert(const value_type& value)
		{
			if (root == nullptr) //若红黑树为空树，则插入结点直接作为根结点
			{
				root = new node(value);
			}
			//找到待插入位置
			node* cur = root;
			node* cur_parent = nullptr;
			while (cur)
			{
				if (value < cur->data)
				{
					cur_parent = cur;
					cur = cur->left;
				}
				else if (value > cur->data)
				{
					cur_parent = cur;
					cur = cur->right;
				}
				else
				{
					return;
				}
			}

			cur = new node(cur_parent, value); //根据所给值构造一个结点
			node* newnode = cur; //记录结点（便于后序返回
			if (value < cur_parent->data)
			{
				//插入到parent的左边
				cur_parent->left = cur;
			}
			else
			{
				//插入到parent的右边
				cur_parent->right = cur;
			}

			//对红黑树进行调整
			while (is_son_self_red(cur_parent))//父结点和待插入节点是红色
			{
				node* cur_grandfather = cur_parent->parent; //parent是红色，则其父结点一定存在
				if (cur_parent == cur_grandfather->left) //parent是grandfather的左孩子
				{
					node* cur_uncle = cur_grandfather->right; //uncle是grandfather的右孩子
					if (cur_uncle && cur_uncle->color == RED) //uncle存在且为红
					{
						//颜色调整
						cur_parent->color = BLACK;
						cur_uncle->color = BLACK;
						cur_grandfather->color = RED;

						//继续往上处理
						cur = cur_grandfather;
						cur_parent = cur->parent;
					}
					else //uncle为黑
					{
						//左左情况
						if (cur == cur_parent->left)
						{
							right_rotate(cur_grandfather); //右单旋
							//颜色调整
							cur_grandfather->color = RED;
							cur_parent->color = BLACK;
						}
						//左右情况
						else //cur == parent->right
						{
							LR_rotate(cur_grandfather); //左右双旋
							//颜色调整
							cur_grandfather->color = RED;
							cur_parent->color = BLACK;
						}
						break; //子树旋转后，该子树的根变成了黑色，无需继续往上进行处理
					}
				}
				else //parent是grandfather的右孩子
				{
					node* cur_uncle = cur_grandfather->left;
					if (cur_uncle && cur_uncle->color == RED)
						{
							//颜色调整
							cur_uncle->color = BLACK;
							cur_parent->color = BLACK;
							cur_grandfather->color = RED;
						//继续往上处理
						cur = cur_grandfather;
						cur_parent = cur->parent;
						}
					else
					{
						//右左情况
						if (cur == cur_parent->left)
						{
							RL_rotate(cur_grandfather); //右左双旋

							//颜色调整
							cur->color = BLACK;
							cur_grandfather->color = RED;
						}
						//右右情况
						else //cur == parent->right
						{
							left_rotate(cur_grandfather); //左单旋
							//颜色调整
							cur_grandfather->color = RED;
							cur_parent->color = BLACK;
						}
						break; //子树旋转后，该子树的根变成了黑色，无需继续往上进行处理
					}
				}
			}
			root->color = BLACK; //根结点的颜色为黑色（可能被情况一变成了红色，需要变回黑色）
		}
		void insert(value_type&& value)
		{
			if (root == nullptr) //若红黑树为空树，则插入结点直接作为根结点
			{
				root = new node(value);
			}
			//找到待插入位置
			node* cur = root;
			node* cur_parent = nullptr;
			while (cur)
			{
				if (value < cur->data)
				{
					cur_parent = cur;
					cur = cur->left;
				}
				else if (value > cur->data)
				{
					cur_parent = cur;
					cur = cur->right;
				}
				else
				{
					return;
				}
			}

			cur = new node(cur_parent, value); //根据所给值构造一个结点
			node* newnode = cur; //记录结点（便于后序返回
			if (value < cur_parent->data)
			{
				//插入到parent的左边
				cur_parent->left = cur;
			}
			else
			{
				//插入到parent的右边
				cur_parent->right = cur;
			}

			//对红黑树进行调整
			while (is_son_self_red(cur_parent))//父结点和待插入节点是红色
			{
				node* cur_grandfather = cur_parent->parent; //parent是红色，则其父结点一定存在
				if (cur_parent == cur_grandfather->left) //parent是grandfather的左孩子
				{
					node* cur_uncle = cur_grandfather->right; //uncle是grandfather的右孩子
					if (cur_uncle && cur_uncle->color == RED) //uncle存在且为红
					{
						//颜色调整
						cur_parent->color = BLACK;
						cur_uncle->color = BLACK;
						cur_grandfather->color = RED;

						//继续往上处理
						cur = cur_grandfather;
						cur_parent = cur->parent;
					}
					else //uncle为黑
					{
						//左左情况
						if (cur == cur_parent->left)
						{
							right_rotate(cur_grandfather); //右单旋
							//颜色调整
							cur_grandfather->color = RED;
							cur_parent->color = BLACK;
						}
						//左右情况
						else //cur == parent->right
						{
							LR_rotate(cur_grandfather); //左右双旋
							//颜色调整
							cur_grandfather->color = RED;
							cur_parent->color = BLACK;
						}
						break; //子树旋转后，该子树的根变成了黑色，无需继续往上进行处理
					}
				}
				else //parent是grandfather的右孩子
				{
					node* cur_uncle = cur_grandfather->left;
					if (cur_uncle && cur_uncle->color == RED)
						{
							//颜色调整
							cur_uncle->color = BLACK;
							cur_parent->color = BLACK;
							cur_grandfather->color = RED;
						//继续往上处理
						cur = cur_grandfather;
						cur_parent = cur->parent;
						}
					else
					{
						//右左情况
						if (cur == cur_parent->left)
						{
							RL_rotate(cur_grandfather); //右左双旋

							//颜色调整
							cur->color = BLACK;
							cur_grandfather->color = RED;
						}
						//右右情况
						else //cur == parent->right
						{
							left_rotate(cur_grandfather); //左单旋
							//颜色调整
							cur_grandfather->color = RED;
							cur_parent->color = BLACK;
						}
						break; //子树旋转后，该子树的根变成了黑色，无需继续往上进行处理
					}
				}
			}
			root->color = BLACK; //根结点的颜色为黑色（可能被情况一变成了红色，需要变回黑色）
		}

		bool erase(value_type& value)
		{
			//用于遍历二叉树
			node* cur_parent = nullptr;
			node* cur = root;
			//用于标记实际的待删除结点及其父结点
			node* delParentPos = nullptr;
			node* delPos = nullptr;
			while (cur)
			{
				if (value < cur->data) //所给key值小于当前结点的key值
				{
					//往该结点的左子树走
					cur_parent = cur;
					cur = cur->left;
				}
				else if (value > cur->data) //所给key值大于当前结点的key值
				{
					//往该结点的右子树走
					cur_parent = cur;
					cur = cur->_right;
				}
				else //找到了待删除结点
				{
					if (cur->left == nullptr) //待删除结点的左子树为空
					{
						if (cur == root) //待删除结点是根结点
						{
							root = root->right; //让根结点的右子树作为新的根结点
							if (root)
							{
								root->parent = nullptr;
								root->color = BLACK; //根结点为黑色
							}
							delete cur; //删除原根结点
							return true;
						}
						else
						{
							delParentPos = cur_parent; //标记实际删除结点的父结点
							delPos = cur; //标记实际删除的结点
						}
						break; //进行红黑树的调整以及结点的实际删除
					}
					else if (cur->right == nullptr) //待删除结点的右子树为空
					{
						if (cur == root) //待删除结点是根结点
						{
							root = root->left; //让根结点的左子树作为新的根结点
							if (root)
							{
								root->parent = nullptr;
								root->color = BLACK; //根结点为黑色
							}
							delete cur; //删除原根结点
							return true;
						}
						else
						{
							delParentPos = cur_parent; //标记实际删除结点的父结点
							delPos = cur; //标记实际删除的结点
						}
						break; //进行红黑树的调整以及结点的实际删除
					}
					else //待删除结点的左右子树均不为空
					{
						//替换法删除
						//寻找待删除结点右子树当中key值最小的结点作为实际删除结点
						node* minParent = cur;
						node* minRight = cur->right;
						while (minRight->left)
						{
							minParent = minRight;
							minRight = minRight->left;
						}
						cur->data = minRight->data; //将待删除结点的key改为minRight的key
						delParentPos = minParent; //标记实际删除结点的父结点
						delPos = minRight; //标记实际删除的结点
						break; //进行红黑树的调整以及结点的实际删除
					}
				}
			}
			if (delPos == nullptr) //delPos没有被修改过，说明没有找到待删除结点
			{
				return false;
			}

			//记录待删除结点及其父结点（用于后续实际删除）
			node* del = delPos;
			node* delP = delParentPos;

			//调整红黑树
			if (delPos->color == BLACK) //删除的是黑色结点
			{
				if (delPos->left) //待删除结点有一个红色的左孩子（不可能是黑色）
				{
					delPos->left->color = BLACK; //将这个红色的左孩子变黑即可
				}
				else if (delPos->right) //待删除结点有一个红色的右孩子（不可能是黑色）
				{
					delPos->right->color = BLACK; //将这个红色的右孩子变黑即可
				}
				else //待删除结点的左右均为空
				{
					while (delPos != root) //可能一直调整到根结点
					{
						if (delPos == delParentPos->left) //待删除结点是其父结点的左孩子
						{
							node* brother = delParentPos->right; //兄弟结点是其父结点的右孩子
							//情况一：brother为红色
							if (brother->color = RED)
							{
								delParentPos->color = RED;
								brother->color = BLACK;
								left_rotate(delParentPos);
								//需要继续处理
								brother = delParentPos->right; //更新brother（否则在本循环中执行其他情况的代码会出错）
							}
							//情况二：brother为黑色，且其左右孩子都是黑色结点或为空
							if (((brother->left == nullptr) || (brother->left->color == BLACK))
								&& ((brother->right == nullptr) || (brother->right->color == BLACK)))
							{
								brother->color = RED;
								if (delParentPos->color = RED)
								{
									delParentPos->color = BLACK;
									break;
								}
								//需要继续处理
								delPos = delParentPos;
								delParentPos = delPos->get_parent();
							}
							else
							{
								//情况三：brother为黑色，且其左孩子是红色结点，右孩子是黑色结点或为空
								if ((brother->right == nullptr) || (brother->right->color == BLACK))
								{
									brother->left->color = BLACK;
									brother->color = RED;
									right_rotate(brother);
									//需要继续处理
									brother = delParentPos->right; //更新brother（否则执行下面情况四的代码会出错）
								}
								//情况四：brother为黑色，且其右孩子是红色结点
								brother->colordelParentPos->color;
								delParentPos->color = BLACK;
								brother->right->color = BLACK;
								left_rotate(delParentPos);
								break; //情况四执行完毕后调整一定结束
							}
						}
						else //delPos == delParentPos->_right //待删除结点是其父结点的左孩子
						{
							node* brother = delParentPos->left; //兄弟结点是其父结点的左孩子
							//情况一：brother为红色
							if (brother->color = RED) //brother为红色
							{
								delParentPos->color = RED;
								brother->color = BLACK;
								right_rotate(delParentPos);
								//需要继续处理
								brother = delParentPos->left; //更新brother（否则在本循环中执行其他情况的代码会出错）
							}
							//情况二：brother为黑色，且其左右孩子都是黑色结点或为空
							if (((brother->left == nullptr) || (brother->left->color == BLACK))
								&& ((brother->right == nullptr) || (brother->right->color == BLACK)))
							{
								brother->color = RED;
								if (delParentPos->color == RED)
								{
									delParentPos->color = BLACK;
									break;
								}
								//需要继续处理
								delPos = delParentPos;
								delParentPos = delPos->get_parent();
							}
							else
							{
								//情况三：brother为黑色，且其右孩子是红色结点，左孩子是黑色结点或为空
								if ((brother->left == nullptr) || (brother->left->color == BLACK))
								{
									brother->right->color = BLACK;
									brother->color = RED;
									left_rotate(brother);
									//需要继续处理
									brother = delParentPos->left; //更新brother（否则执行下面情况四的代码会出错）
								}
								//情况四：brother为黑色，且其左孩子是红色结点
								else if (!brother->color);
								{
									delParentPos->color = BLACK;
									brother->left->color = BLACK;
									right_rotate(delParentPos);
									break; //情况四执行完毕后调整一定结束
								}
							}
						}
					}
				}
			}
			//进行实际删除
			if (del->left == nullptr) //实际删除结点的左子树为空
			{
				if (del == delP->left) //实际删除结点是其父结点的左孩子
				{
					delP->set_left(del->right);
					if (del->right)
						del->right->parent = delP;
				}
				else //实际删除结点是其父结点的右孩子
				{
					delP->set_right(del->right);
					if (del->right)
						del->right->parent = delP;
				}
			}
			else //实际删除结点的右子树为空
			{
				if (del == delP->left) //实际删除结点是其父结点的左孩子
				{
					delP->set_left(del->left);
					if (del->left)
						del->left->parent = delP;
				}
				else //实际删除结点是其父结点的右孩子
				{
					delP->set_right(del->left);
					if (del->left)
						del->left->parent = delP;
				}
			}
			free(del); //实际删除结点
			return true;
		}
		bool erase(const value_type& value)
		{
			//用于遍历二叉树
			node* cur_parent = nullptr;
			node* cur = root;
			//用于标记实际的待删除结点及其父结点
			node* delParentPos = nullptr;
			node* delPos = nullptr;
			while (cur)
			{
				if (value < cur->data) //所给key值小于当前结点的key值
				{
					//往该结点的左子树走
					cur_parent = cur;
					cur = cur->left;
				}
				else if (value > cur->data) //所给key值大于当前结点的key值
				{
					//往该结点的右子树走
					cur_parent = cur;
					cur = cur->_right;
				}
				else //找到了待删除结点
				{
					if (cur->left == nullptr) //待删除结点的左子树为空
					{
						if (cur == root) //待删除结点是根结点
						{
							root = root->right; //让根结点的右子树作为新的根结点
							if (root)
							{
								root->parent = nullptr;
								root->color = BLACK; //根结点为黑色
							}
							free(cur); //删除原根结点
							return true;
						}
						else
						{
							delParentPos = cur_parent; //标记实际删除结点的父结点
							delPos = cur; //标记实际删除的结点
						}
						break; //进行红黑树的调整以及结点的实际删除
					}
					else if (cur->right == nullptr) //待删除结点的右子树为空
					{
						if (cur == root) //待删除结点是根结点
						{
							root = root->left; //让根结点的左子树作为新的根结点
							if (root)
							{
								root->parent = nullptr;
								root->color = BLACK; //根结点为黑色
							}
							free(cur); //删除原根结点
							return true;
						}
						else
						{
							delParentPos = cur_parent; //标记实际删除结点的父结点
							delPos = cur; //标记实际删除的结点
						}
						break; //进行红黑树的调整以及结点的实际删除
					}
					else //待删除结点的左右子树均不为空
					{
						//替换法删除
						//寻找待删除结点右子树当中key值最小的结点作为实际删除结点
						node* minParent = cur;
						node* minRight = cur->right;
						while (minRight->left)
						{
							minParent = minRight;
							minRight = minRight->left;
						}
						cur->data = minRight->data; //将待删除结点的key改为minRight的key
						delParentPos = minParent; //标记实际删除结点的父结点
						delPos = minRight; //标记实际删除的结点
						break; //进行红黑树的调整以及结点的实际删除
					}
				}
			}
			if (delPos == nullptr) //delPos没有被修改过，说明没有找到待删除结点
			{
				return false;
			}

			//记录待删除结点及其父结点（用于后续实际删除）
			node* del = delPos;
			node* delP = delParentPos;

			//调整红黑树
			if (delPos->color == BLACK) //删除的是黑色结点
			{
				if (delPos->left) //待删除结点有一个红色的左孩子（不可能是黑色）
				{
					delPos->left->color = BLACK; //将这个红色的左孩子变黑即可
				}
				else if (delPos->right) //待删除结点有一个红色的右孩子（不可能是黑色）
				{
					delPos->right->color = BLACK; //将这个红色的右孩子变黑即可
				}
				else //待删除结点的左右均为空
				{
					while (delPos != root) //可能一直调整到根结点
					{
						if (delPos == delParentPos->left) //待删除结点是其父结点的左孩子
						{
							node* brother = delParentPos->right; //兄弟结点是其父结点的右孩子
							//情况一：brother为红色
							if (brother->color = RED)
							{
								delParentPos->color = RED;
								brother->color = BLACK;
								left_rotate(delParentPos);
								//需要继续处理
								brother = delParentPos->right; //更新brother（否则在本循环中执行其他情况的代码会出错）
							}
							//情况二：brother为黑色，且其左右孩子都是黑色结点或为空
							if (((brother->left == nullptr) || (brother->left->color == BLACK))
								&& ((brother->right == nullptr) || (brother->right->color == BLACK)))
							{
								brother->color = RED;
								if (delParentPos->color = RED)
								{
									delParentPos->color = BLACK;
									break;
								}
								//需要继续处理
								delPos = delParentPos;
								delParentPos = delPos->get_parent();
							}
							else
							{
								//情况三：brother为黑色，且其左孩子是红色结点，右孩子是黑色结点或为空
								if ((brother->right == nullptr) || (brother->right->color == BLACK))
								{
									brother->left->color = BLACK;
									brother->color = RED;
									right_rotate(brother);
									//需要继续处理
									brother = delParentPos->right; //更新brother（否则执行下面情况四的代码会出错）
								}
								//情况四：brother为黑色，且其右孩子是红色结点
								brother->colordelParentPos->color;
								delParentPos->color = BLACK;
								brother->right->color = BLACK;
								left_rotate(delParentPos);
								break; //情况四执行完毕后调整一定结束
							}
						}
						else //delPos == delParentPos->_right //待删除结点是其父结点的左孩子
						{
							node* brother = delParentPos->left; //兄弟结点是其父结点的左孩子
							//情况一：brother为红色
							if (brother->color = RED) //brother为红色
							{
								delParentPos->color = RED;
								brother->color = BLACK;
								right_rotate(delParentPos);
								//需要继续处理
								brother = delParentPos->left; //更新brother（否则在本循环中执行其他情况的代码会出错）
							}
							//情况二：brother为黑色，且其左右孩子都是黑色结点或为空
							if (((brother->left == nullptr) || (brother->left->color == BLACK))
								&& ((brother->right == nullptr) || (brother->right->color == BLACK)))
							{
								brother->color = RED;
								if (delParentPos->color == RED)
								{
									delParentPos->color = BLACK;
									break;
								}
								//需要继续处理
								delPos = delParentPos;
								delParentPos = delPos->get_parent();
							}
							else
							{
								//情况三：brother为黑色，且其右孩子是红色结点，左孩子是黑色结点或为空
								if ((brother->left == nullptr) || (brother->left->color == BLACK))
								{
									brother->get_right->color = BLACK;
									brother->color = RED;
									left_rotate(brother);
									//需要继续处理
									brother = delParentPos->left; //更新brother（否则执行下面情况四的代码会出错）
								}
								//情况四：brother为黑色，且其左孩子是红色结点
								else if(!brother->color)
								{
									delParentPos->color = BLACK;
									brother->left->color = BLACK;
									right_rotate(delParentPos);
									break; //情况四执行完毕后调整一定结束
								}
							}
						}
					}
				}
			}
			//进行实际删除
			if (del->left == nullptr) //实际删除结点的左子树为空
			{
				if (del == delP->left) //实际删除结点是其父结点的左孩子
				{
					delP->set_left(del->right);
					if (del->right)
						del->right->parent = delP;
				}
				else //实际删除结点是其父结点的右孩子
				{
					delP->set_right(del->right);
					if (del->right)
						del->right->parent = delP;
				}
			}
			else //实际删除结点的右子树为空
			{
				if (del == delP->left) //实际删除结点是其父结点的左孩子
				{
					delP->set_left(del->left);
					if (del->left)
						del->left->parent = delP;
				}
				else //实际删除结点是其父结点的右孩子
				{
					delP->set_right(del->left);
					if (del->left)
						del->left->parent = delP;
				}
			}
			free(del); //实际删除结点
			return true;
		}
		bool erase(value_type&& value)
		{
			//用于遍历二叉树
			node* cur_parent = nullptr;
			node* cur = root;
			//用于标记实际的待删除结点及其父结点
			node* delParentPos = nullptr;
			node* delPos = nullptr;
			while (cur)
			{
				if (value < cur->data) //所给key值小于当前结点的key值
				{
					//往该结点的左子树走
					cur_parent = cur;
					cur = cur->left;
				}
				else if (value > cur->data) //所给key值大于当前结点的key值
				{
					//往该结点的右子树走
					cur_parent = cur;
					cur = cur->right;
				}
				else //找到了待删除结点
				{
					if (cur->left == nullptr) //待删除结点的左子树为空
					{
						if (cur == root) //待删除结点是根结点
						{
							root = root->right; //让根结点的右子树作为新的根结点
							if (root)
							{
								root->parent = nullptr;
								root->color = BLACK; //根结点为黑色
							}
							free(cur); //删除原根结点
							return true;
						}
						else
						{
							delParentPos = cur_parent; //标记实际删除结点的父结点
							delPos = cur; //标记实际删除的结点
						}
						break; //进行红黑树的调整以及结点的实际删除
					}
					else if (cur->right == nullptr) //待删除结点的右子树为空
					{
						if (cur == root) //待删除结点是根结点
						{
							root = root->left; //让根结点的左子树作为新的根结点
							if (root)
							{
								root->parent = nullptr;
								root->color = BLACK; //根结点为黑色
							}
							free(cur); //删除原根结点
							return true;
						}
						else
						{
							delParentPos = cur_parent; //标记实际删除结点的父结点
							delPos = cur; //标记实际删除的结点
						}
						break; //进行红黑树的调整以及结点的实际删除
					}
					else //待删除结点的左右子树均不为空
					{
						//替换法删除
						//寻找待删除结点右子树当中key值最小的结点作为实际删除结点
						node* minParent = cur;
						node* minRight = cur->right;
						while (minRight->left)
						{
							minParent = minRight;
							minRight = minRight->left;
						}
						cur->data = minRight->data; //将待删除结点的key改为minRight的key
						delParentPos = minParent; //标记实际删除结点的父结点
						delPos = minRight; //标记实际删除的结点
						break; //进行红黑树的调整以及结点的实际删除
					}
				}
			}
			if (delPos == nullptr) //delPos没有被修改过，说明没有找到待删除结点
			{
				return false;
			}

			//记录待删除结点及其父结点（用于后续实际删除）
			node* del = delPos;
			node* delP = delParentPos;

			//调整红黑树
			if (delPos->color == BLACK) //删除的是黑色结点
			{
				if (delPos->left) //待删除结点有一个红色的左孩子（不可能是黑色）
				{
					delPos->left->color = BLACK; //将这个红色的左孩子变黑即可
				}
				else if (delPos->right) //待删除结点有一个红色的右孩子（不可能是黑色）
				{
					delPos->right->color = BLACK; //将这个红色的右孩子变黑即可
				}
				else //待删除结点的左右均为空
				{
					while (delPos != root) //可能一直调整到根结点
					{
						if (delPos == delParentPos->left) //待删除结点是其父结点的左孩子
						{
							node* brother = delParentPos->right; //兄弟结点是其父结点的右孩子
							//情况一：brother为红色
							if (brother->color = RED)
							{
								delParentPos->color = RED;
								brother->color = BLACK;
								left_rotate(delParentPos);
								//需要继续处理
								brother = delParentPos->right; //更新brother（否则在本循环中执行其他情况的代码会出错）
							}
							//情况二：brother为黑色，且其左右孩子都是黑色结点或为空
							if (((brother->left == nullptr) || (brother->left->color == BLACK))
								&& ((brother->right == nullptr) || (brother->right->color == BLACK)))
							{
								brother->color = RED;
								if (delParentPos->color = RED)
								{
									delParentPos->color = BLACK;
									break;
								}
								//需要继续处理
								delPos = delParentPos;
								delParentPos = delPos->parent;
							}
							else
							{
								//情况三：brother为黑色，且其左孩子是红色结点，右孩子是黑色结点或为空
								if ((brother->right == nullptr) || (brother->right->color == BLACK))
								{
									brother->left->color = BLACK;
									brother->color = RED;
									right_rotate(brother);
									//需要继续处理
									brother = delParentPos->right; //更新brother（否则执行下面情况四的代码会出错）
								}
								//情况四：brother为黑色，且其右孩子是红色结点
								brother->color = RED;
								delParentPos->color = BLACK;
								brother->right->color = BLACK;
								left_rotate(delParentPos);
								break; //情况四执行完毕后调整一定结束
							}
						}
						else //delPos == delParentPos->_right //待删除结点是其父结点的左孩子
						{
							node* brother = delParentPos->left; //兄弟结点是其父结点的左孩子
							//情况一：brother为红色
							if (brother->color = RED) //brother为红色
							{
								delParentPos->color = RED;
								brother->color = BLACK;
								right_rotate(delParentPos);
								//需要继续处理
								brother = delParentPos->left; //更新brother（否则在本循环中执行其他情况的代码会出错）
							}
							//情况二：brother为黑色，且其左右孩子都是黑色结点或为空
							if (((brother->left == nullptr) || (brother->left->color == BLACK))
								&& ((brother->right == nullptr) || (brother->right->color == BLACK)))
							{
								brother->color = RED;
								if (delParentPos->color == RED)
								{
									delParentPos->color = BLACK;
									break;
								}
								//需要继续处理
								delPos = delParentPos;
								delParentPos = delPos->parent;
							}
							else
							{
								//情况三：brother为黑色，且其右孩子是红色结点，左孩子是黑色结点或为空
								if ((brother->left == nullptr) || (brother->left->color == BLACK))
								{
									brother->right->color = BLACK;
									brother->color = RED;
									left_rotate(brother);
									//需要继续处理
									brother = delParentPos->left; //更新brother（否则执行下面情况四的代码会出错）
								}
								//情况四：brother为黑色，且其左孩子是红色结点
								else if(!brother->color);
								{
									delParentPos->color = BLACK;
									brother->left->color = BLACK;
									right_rotate(delParentPos);
									break; //情况四执行完毕后调整一定结束
								}
							}
						}
					}
				}
			}
			//进行实际删除
			if (del->left == nullptr) //实际删除结点的左子树为空
			{
				if (del == delP->left) //实际删除结点是其父结点的左孩子
				{
					delP->left = (del->right);
					if (del->right)
						del->right->parent = delP;
				}
				else //实际删除结点是其父结点的右孩子
				{
					delP->right = (del->right);
					if (del->right)
						del->right->parent = delP;
				}
			}
			else //实际删除结点的右子树为空
			{
				if (del == delP->left) //实际删除结点是其父结点的左孩子
				{
					delP->left = (del->left);
					if (del->left)
						del->left->parent = delP;
				}
				else //实际删除结点是其父结点的右孩子
				{
					delP->right = (del->left);
					if (del->left)
						del->left->parent = delP;
				}
			}
			free(del); //实际删除结点
			return true;
		}
		void clear()
		{
			free(root);
			root = nullptr;
		}
		bool empty()
		{
			return root == nullptr;
		}
		node* find(const value_type& value)
		{
			node* cur = root;
			while (cur)
			{
				if (value < cur->data) //key值小于该结点的值
				{
					cur = cur->left; //在该结点的左子树当中查找
				}
				else if (value > cur->data) //key值大于该结点的值
				{
					cur = cur->right; //在该结点的右子树当中查找
				}
				else //找到了目标结点
				{
					return cur; //返回该结点
				}
			}
			return nullptr; //查找失败
		}
		node* find(value_type& value)
		{
			node* cur = root;
			while (cur)
			{
				if (value < cur->data) //key值小于该结点的值
				{
					cur = cur->left; //在该结点的左子树当中查找
				}
				else if (value > cur->data) //key值大于该结点的值
				{
					cur = cur->right; //在该结点的右子树当中查找
				}
				else //找到了目标结点
				{
					return cur; //返回该结点
				}
			}
			return nullptr; //查找失败
		}
		node* find(value_type&& value)
		{
			node* cur = root;
			while (cur)
			{
				if (value < cur->data) //key值小于该结点的值
				{
					cur = cur->left; //在该结点的左子树当中查找
				}
				else if (value > cur->data) //key值大于该结点的值
				{
					cur = cur->right; //在该结点的右子树当中查找
				}
				else //找到了目标结点
				{
					return cur; //返回该结点
				}
			}
			return nullptr; //查找失败
		}
	private:
		bool root_is_black()
		{
			return root->color == BLACK;
		}
		bool is_son_self_red(node*& insert)
		{
			if (insert->color == RED)
			{
				if (insert->parent->color == RED)
				{
					return true;
				}
			}
			return false;
		}
		//左旋
		void left_rotate(node*& cparent)
		{
			node* subR = cparent->right;
			node* subRL = subR->left;
			node* cparentParent = cparent->parent;
			//建立subRL与parent之间的联系
			cparent->right = subRL;
			if (subRL)
				subRL->parent = cparent;

			//建立parent与subR之间的联系
			subR->left = (cparent);
			cparent->parent = subR;

			//建立subR与parentParent之间的联系
			if (cparentParent == nullptr)
			{
				root = subR;
				root->parent = nullptr;
			}
			else
			{
				if (cparent == cparentParent->left)
				{
					cparentParent->left = subR;
				}
				else
				{
					cparentParent->right = subR;
				}
				subR->parent = cparentParent;
			}
		}
		//右旋
		void right_rotate(node*& cparent)
		{
			node* subL = cparent->left;
			node* subLR = subL->right;
			node* cparentParent = cparent->parent;

			//建立subLR与parent之间的联系
			cparent->left = subLR;
			if (subLR)
				subLR->parent = cparent;

			//建立parent与subL之间的联系
			subL->right = cparent;
			cparent->parent = subL;

			//建立subL与parentParent之间的联系
			if (cparentParent == nullptr)
			{
				root = subL;
				root->parent = nullptr;
			}
			else
			{
				if (cparent == cparentParent->left)
				{
					cparentParent->left = subL;
				}
				else
				{
					cparentParent->right = subL;
				}
				subL->parent = cparentParent;
			}
		}

		//左右双旋
		void LR_rotate(node*& cparent)
		{
			left_rotate(cparent);
			right_rotate(cparent->left);
		}
		void RL_rotate(node*& cparent)
		{
			right_rotate(cparent);
			left_rotate(cparent->right);
		}
	private:
		node* root;
		size_t size;
	};

}
#endif //MY_STL_RED_BLACK_TREE