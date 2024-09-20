#pragma once
#ifndef RED_BLACK_TREE
#define RED_BLACK_TREE
#include "Allocator.h"

/* https://blog.csdn.net/chenlong_cxy/article/details/121481859 尊师教导*/
//存储获取值的种类
template <class T>
class RBNode
{
public:
	using RED = true;
	using BLACK = false;
	RBNode(T& value) :parent(nullptr), left(nullptr), right(nullptr), data(T()), color(black)//根节点
	{
	}
	RBNode(RBNode* parent_value) :parent(parent_value), left(nullptr), right(nullptr), data(T()),color(red)
	{
	}
	RBNode(RBNode* parent_value, T& value) :parent(parent_value), left(nullptr), right(nullptr), data(value)
	{
	}
	~RBNode()
	{
		operator delete left;
		left = nullptr;
		operator delete right;
		right = nullptr;
		operator delete parent;
		parent = nullptr;
	}
	void set_left(RBNode* value)
	{
		left = value;
	}
	void set_right(RBNode* value)
	{
		right = value;
	}
	void set_parent(RBNode* value)
	{
		parent = value;
	}
	void set_data(T value)
	{
		data = value;
	}
	void set_color(bool value)
	{
		color = value;
	}
	bool get_color()
	{
		return color;
	}
	RBNode* get_left()
	{
		return left;
	}
	RBNode* get_right()
	{
		return right;
	}
	RBNode* get_parent()
	{
		return parent;
	}
	T get_data()
	{
		return data;
	}
	bool operator == (const RBNode& value)
	{
		if ((data == value.data) && (left == value.left) && (right == value.right) && (parent == value.parent) && (color == value.color))
		{
			return true;
		}
		return false;
	}
private:
	bool color;
	RBNode* left;
	RBNode* right;
	RBNode* parent;
	T data;
};

namespace STL
{
	template <class T>
	struct RBTree
	{
		using T = value_type;
		using node = RBNode<T>;
	public:
		RBTree() :root(nullptr)
		{
		}
		~RBTree()
		{
			operator delete root;
			root = nullptr;
		}
		void insert(value_type& value)
		{
			if (root == nullptr) //若红黑树为空树，则插入结点直接作为根结点
			{
				root = new node <value_type>(value);
			}
			//找到待插入位置
			node* cur = root;
			node* cur_parent = nullptr;
			while (cur)
			{
				if (value < cur->get_data())
				{
					//往该结点的左子树走
					parent = cur;
					cur = cur->left;
				}
				else if (value > cur->get_data())
				{
					//往该结点的右子树走
					parent = cur;
					cur = cur->right;
				}
				else
				{
					return;
				}
			}

			cur = new node<value_type>(parent,value); //根据所给值构造一个结点
			node* newnode = cur; //记录结点（便于后序返回
			if (value < cur_parent->get_data())
			{
				//插入到parent的左边
				cur_parent->set_left(cur);
			}
			else
			{
				//插入到parent的右边
				cur_parent->set_right(cur);
			}

			//对红黑树进行调整
			while (is_son_self_red(cur_parent))
			{
				node* cur_grandfather = cur_parent->parent; //parent是红色，则其父结点一定存在
				if (parent == grandfather->get_left()) //parent是grandfather的左孩子
				{
					node* cur_uncle = cur_grandfather->get_right(); //uncle是grandfather的右孩子
					if (cur_uncle && uncle->get_color() == node::RED) //情况1：uncle存在且为红
					{
						//颜色调整
						parent->set_color(node::BLACK);
						uncle->set_color(node::BLACK);
						grandfather->set_color(node::RED);

						//继续往上处理
						cur = cur_grandfather;
						cur_parent = cur->parent;
					}
					else //uncle为黑
					{
						if (cur == cur_parent->get_left())
						{
							right_rotate(grandfather); //右单旋

							//颜色调整
							cur_grandfather->set_color(node::RED);
							cur_parent->set_color(node::BLACK);
						}
						else //cur == parent->_right
						{
							LR_rotate(cur_grandfather); //左右双旋

							//颜色调整
							cur_grandfather->set_color(node::RED);
							cur_parent->set_color(node::BLACK);
						}
						break; //子树旋转后，该子树的根变成了黑色，无需继续往上进行处理
					}
				}
				else //parent是grandfather的右孩子
				{
					node* cur_uncle = cur_grandfather->get_left();
					if (cur_uncle && cur_uncle->get_color() == node::RED) //情况1：uncle存在且为红
					{
						//颜色调整
						cur_uncle->set_color(node::BLACK);
						cur_parent->set_color(node::BLACK);
						cur_grandfather->get_color(node::RED);

						//继续往上处理
						cur = cur_grandfather;
						cur_parent = cur->parent;
					}
					else //情况2+情况3：uncle不存在 + uncle存在且为黑
					{
						if (cur == cur_parent->get_left())
						{
							RL_rotate(cur_grandfather); //右左双旋

							//颜色调整
							cur->set_color(node::BLACK);
							cur_grandfather->set_color(node::RED);
						}
						else //cur == parent->_right
						{
							left_rotate(cur_grandfather); //左单旋
							//颜色调整
							cur_grandfather->set_color(node::RED);
							cur_parent->set_color(node::BLACK);
						}
						break; //子树旋转后，该子树的根变成了黑色，无需继续往上进行处理
					}
				}
			}
			root->set_color(node::BLACK); //根结点的颜色为黑色（可能被情况一变成了红色，需要变回黑色）
		}
		void insert(const value_type& value)
		{
			if (root == nullptr) //若红黑树为空树，则插入结点直接作为根结点
			{
				root = new node <value_type>(value);
			}
			//找到待插入位置
			node* cur = root;
			node* cur_parent = nullptr;
			while (cur)
			{
				if (value < cur->get_data())
				{
					//往该结点的左子树走
					parent = cur;
					cur = cur->left;
				}
				else if (value > cur->get_data())
				{
					//往该结点的右子树走
					parent = cur;
					cur = cur->right;
				}
				else
				{
					return;
				}
			}

			cur = new node<value_type>(parent, value); //根据所给值构造一个结点
			node* newnode = cur; //记录结点（便于后序返回
			if (value < cur_parent->get_data())
			{
				//插入到parent的左边
				cur_parent->set_left(cur);
			}
			else
			{
				//插入到parent的右边
				cur_parent->set_right(cur);
			}

			//对红黑树进行调整
			while (is_son_self_red(cur_parent))
			{
				node* cur_grandfather = cur_parent->parent; //parent是红色，则其父结点一定存在
				if (parent == grandfather->get_left()) //parent是grandfather的左孩子
				{
					node* cur_uncle = cur_grandfather->get_right(); //uncle是grandfather的右孩子
					if (cur_uncle && uncle->get_color() == node::RED) //情况1：uncle存在且为红
					{
						//颜色调整
						parent->set_color(node::BLACK);
						uncle->set_color(node::BLACK);
						grandfather->set_color(node::RED);

						//继续往上处理
						cur = cur_grandfather;
						cur_parent = cur->parent;
					}
					else //uncle为黑
					{
						if (cur == cur_parent->get_left())
						{
							right_rotate(grandfather); //右单旋

							//颜色调整
							cur_grandfather->set_color(node::RED);
							cur_parent->set_color(node::BLACK);
						}
						else //cur == parent->_right
						{
							LR_rotate(cur_grandfather); //左右双旋

							//颜色调整
							cur_grandfather->set_color(node::RED);
							cur_parent->set_color(node::BLACK);
						}
						break; //子树旋转后，该子树的根变成了黑色，无需继续往上进行处理
					}
				}
				else //parent是grandfather的右孩子
				{
					node* cur_uncle = cur_grandfather->get_left();
					if (cur_uncle && cur_uncle->get_color() == node::RED) //情况1：uncle存在且为红
					{
						//颜色调整
						cur_uncle->set_color(node::BLACK);
						cur_parent->set_color(node::BLACK);
						cur_grandfather->get_color(node::RED);

						//继续往上处理
						cur = cur_grandfather;
						cur_parent = cur->parent;
					}
					else //情况2+情况3：uncle不存在 + uncle存在且为黑
					{
						if (cur == cur_parent->get_left())
						{
							RL_rotate(cur_grandfather); //右左双旋

							//颜色调整
							cur->set_color(node::BLACK);
							cur_grandfather->set_color(node::RED);
						}
						else //cur == parent->_right
						{
							left_rotate(cur_grandfather); //左单旋
							//颜色调整
							cur_grandfather->set_color(node::RED);
							cur_parent->set_color(node::BLACK);
						}
						break; //子树旋转后，该子树的根变成了黑色，无需继续往上进行处理
					}
				}
			}
			root->set_color(node::BLACK); //根结点的颜色为黑色（可能被情况一变成了红色，需要变回黑色）
		}
		void insert(value_type&& value)
		{
			if (root == nullptr) //若红黑树为空树，则插入结点直接作为根结点
			{
				root = new node <value_type>(value);
			}
			//找到待插入位置
			node* cur = root;
			node* cur_parent = nullptr;
			while (cur)
			{
				if (value < cur->get_data())
				{
					//往该结点的左子树走
					parent = cur;
					cur = cur->left;
				}
				else if (value > cur->get_data())
				{
					//往该结点的右子树走
					parent = cur;
					cur = cur->right;
				}
				else
				{
					return;
				}
			}

			cur = new node<value_type>(parent, value); //根据所给值构造一个结点
			node* newnode = cur; //记录结点（便于后序返回
			if (value < cur_parent->get_data())
			{
				//插入到parent的左边
				cur_parent->set_left(cur);
			}
			else
			{
				//插入到parent的右边
				cur_parent->set_right(cur);
			}

			//对红黑树进行调整
			while (is_son_self_red(cur_parent))
			{
				node* cur_grandfather = cur_parent->parent; //parent是红色，则其父结点一定存在
				if (parent == grandfather->get_left()) //parent是grandfather的左孩子
				{
					node* cur_uncle = cur_grandfather->get_right(); //uncle是grandfather的右孩子
					if (cur_uncle && uncle->get_color() == node::RED) //情况1：uncle存在且为红
					{
						//颜色调整
						parent->set_color(node::BLACK);
						uncle->set_color(node::BLACK);
						grandfather->set_color(node::RED);

						//继续往上处理
						cur = cur_grandfather;
						cur_parent = cur->parent;
					}
					else //uncle为黑
					{
						if (cur == cur_parent->get_left())
						{
							right_rotate(grandfather); //右单旋

							//颜色调整
							cur_grandfather->set_color(node::RED);
							cur_parent->set_color(node::BLACK);
						}
						else //cur == parent->_right
						{
							LR_rotate(cur_grandfather); //左右双旋

							//颜色调整
							cur_grandfather->set_color(node::RED);
							cur_parent->set_color(node::BLACK);
						}
						break; //子树旋转后，该子树的根变成了黑色，无需继续往上进行处理
					}
				}
				else //parent是grandfather的右孩子
				{
					node* cur_uncle = cur_grandfather->get_left();
					if (cur_uncle && cur_uncle->get_color() == node::RED) //情况1：uncle存在且为红
					{
						//颜色调整
						cur_uncle->set_color(node::BLACK);
						cur_parent->set_color(node::BLACK);
						cur_grandfather->get_color(node::RED);

						//继续往上处理
						cur = cur_grandfather;
						cur_parent = cur->parent;
					}
					else //情况2+情况3：uncle不存在 + uncle存在且为黑
					{
						if (cur == cur_parent->get_left())
						{
							RL_rotate(cur_grandfather); //右左双旋

							//颜色调整
							cur->set_color(node::BLACK);
							cur_grandfather->set_color(node::RED);
						}
						else //cur == parent->_right
						{
							left_rotate(cur_grandfather); //左单旋
							//颜色调整
							cur_grandfather->set_color(node::RED);
							cur_parent->set_color(node::BLACK);
						}
						break; //子树旋转后，该子树的根变成了黑色，无需继续往上进行处理
					}
				}
			}
			root->set_color(node::BLACK); //根结点的颜色为黑色（可能被情况一变成了红色，需要变回黑色）
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
				if (value < cur->get_data()) //所给key值小于当前结点的key值
				{
					//往该结点的左子树走
					cur_parent = cur;
					cur = cur->get_left();
				}
				else if (value > cur->get_data()) //所给key值大于当前结点的key值
				{
					//往该结点的右子树走
					cur_parent = cur;
					cur = cur->_right;
				}
				else //找到了待删除结点
				{
					if (cur->get_left() == nullptr) //待删除结点的左子树为空
					{
						if (cur == root) //待删除结点是根结点
						{
							root = root->get_right(); //让根结点的右子树作为新的根结点
							if (root)
							{
								root->set_parent(nullptr);
								root->set_color(node::BLACK); //根结点为黑色
							}
							operator delete cur; //删除原根结点
							return true;
						}
						else
						{
							delParentPos = cparent; //标记实际删除结点的父结点
							delPos = cur; //标记实际删除的结点
						}
						break; //进行红黑树的调整以及结点的实际删除
					}
					else if (cur->get_right() == nullptr) //待删除结点的右子树为空
					{
						if (cur == root) //待删除结点是根结点
						{
							root = root->get_left(); //让根结点的左子树作为新的根结点
							if (root)
							{
								root->set_parent(nullptr);
								root->set_color(BLACK); //根结点为黑色
							}
							operator delete cur; //删除原根结点
							return true;
						}
						else
						{
							delParentPos = cparent; //标记实际删除结点的父结点
							delPos = cur; //标记实际删除的结点
						}
						break; //进行红黑树的调整以及结点的实际删除
					}
					else //待删除结点的左右子树均不为空
					{
						//替换法删除
						//寻找待删除结点右子树当中key值最小的结点作为实际删除结点
						node* minParent = cur;
						node* minRight = cur->get_right();
						while (minRight->get_left())
						{
							minParent = minRight;
							minRight = minRight->get_left();
						}
						cur->set_data(minRight->get_data()); //将待删除结点的key改为minRight的key
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
			if (delPos->get_color() == node::BLACK) //删除的是黑色结点
			{
				if (delPos->get_left()) //待删除结点有一个红色的左孩子（不可能是黑色）
				{
					delPos->get_left()->set_color(node::BLACK); //将这个红色的左孩子变黑即可
				}
				else if (delPos->get_right()) //待删除结点有一个红色的右孩子（不可能是黑色）
				{
					delPos->get_right()->set_color(node::BLACK); //将这个红色的右孩子变黑即可
				}
				else //待删除结点的左右均为空
				{
					while (delPos != root) //可能一直调整到根结点
					{
						if (delPos == delParentPos->get_left()) //待删除结点是其父结点的左孩子
						{
							node* brother = delParentPos->get_right(); //兄弟结点是其父结点的右孩子
							//情况一：brother为红色
							if (brother->set_color(node::RED))
							{
								delParentPos->set_color(node::RED);
								brother->set_color(node::BLACK);
								left_rotate(delParentPos);
								//需要继续处理
								brother = delParentPos->get_right(); //更新brother（否则在本循环中执行其他情况的代码会出错）
							}
							//情况二：brother为黑色，且其左右孩子都是黑色结点或为空
							if (((brother->get_left() == nullptr) || (brother->get_left()->get_color() == node::BLACK))
								&& ((brother->get_right() == nullptr) || (brother->get_right()->get_color() == node::BLACK)))
							{
								brother->set_color(node::RED);
								if (delParentPos->set_color(node::RED))
								{
									delParentPos->set_color(node::BLACK);
									break;
								}
								//需要继续处理
								delPos = delParentPos;
								delParentPos = delPos->get_parent();
							}
							else
							{
								//情况三：brother为黑色，且其左孩子是红色结点，右孩子是黑色结点或为空
								if ((brother->get_right() == nullptr) || (brother->get_right()->get_color() == node::BLACK))
								{
									brother->get_left()->set_color(node::BLACK);
									brother->set_color(node::RED);
									right_rotate(brother);
									//需要继续处理
									brother = delParentPos->get_right(); //更新brother（否则执行下面情况四的代码会出错）
								}
								//情况四：brother为黑色，且其右孩子是红色结点
								brother->set_color(delParentPos->get_color());
								delParentPos->set_color(node::BLACK);
								brother->get_right()->set_color(node::BLACK);
								left_rotate(delParentPos);
								break; //情况四执行完毕后调整一定结束
							}
						}
						else //delPos == delParentPos->_right //待删除结点是其父结点的左孩子
						{
							node* brother = delParentPos->get_left(); //兄弟结点是其父结点的左孩子
							//情况一：brother为红色
							if (brother->set_color(node::RED)) //brother为红色
							{
								delParentPos->set_color(node::RED);
								brother->set_color(node::BLACK);
								right_rotate(delParentPos);
								//需要继续处理
								brother = delParentPos->get_left(); //更新brother（否则在本循环中执行其他情况的代码会出错）
							}
							//情况二：brother为黑色，且其左右孩子都是黑色结点或为空
							if (((brother->get_left() == nullptr) || (brother->get_left()->get_color() == node::BLACK))
								&& ((brother->get_right() == nullptr) || (brother->get_right()->get_color() == node::BLACK)))
							{
								brother->set_color(node::RED);
								if (delParentPos->get_color() == node::RED)
								{
									delParentPos->set_color(node::BLACK);
									break;
								}
								//需要继续处理
								delPos = delParentPos;
								delParentPos = delPos->get_parent();
							}
							else
							{
								//情况三：brother为黑色，且其右孩子是红色结点，左孩子是黑色结点或为空
								if ((brother->get_left() == nullptr) || (brother->get_left()->get_color() == node::BLACK))
								{
									brother->get_right->set_color(node::BLACK);
									brother->set_color(node::RED);
									left_rotate(brother);
									//需要继续处理
									brother = delParentPos->get_left(); //更新brother（否则执行下面情况四的代码会出错）
								}
								//情况四：brother为黑色，且其左孩子是红色结点
								brother->set_color(delParentPos->get_color());
								delParentPos->set_color(node::BLACK);
								brother->get_left()->set_color(node::BLACK);
								right_rotate(delParentPos);
								break; //情况四执行完毕后调整一定结束
							}
						}
					}
				}
			}
			//进行实际删除
			if (del->get_left() == nullptr) //实际删除结点的左子树为空
			{
				if (del == delP->get_left()) //实际删除结点是其父结点的左孩子
				{
					delP->set_left(del->get_right());
					if (del->get_right())
						del->get_right()->set_parent(delp);
				}
				else //实际删除结点是其父结点的右孩子
				{
					delP->set_right(del->get_right());
					if (del->get_right())
						del->get_right()->set_parent(delp);
				}
			}
			else //实际删除结点的右子树为空
			{
				if (del == delP->get_left()) //实际删除结点是其父结点的左孩子
				{
					delP->set_left(del->get_left());
					if (del->get_left())
						del->get_left()->set_parent(delP);
				}
				else //实际删除结点是其父结点的右孩子
				{
					delP->set_right(del->get_left());
					if (del->get_left())
						del->get_left()->set_parent(delP);
				}
			}
			operator delete del; //实际删除结点
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
				if (value < cur->get_data()) //所给key值小于当前结点的key值
				{
					//往该结点的左子树走
					cur_parent = cur;
					cur = cur->get_left();
				}
				else if (value > cur->get_data()) //所给key值大于当前结点的key值
				{
					//往该结点的右子树走
					cur_parent = cur;
					cur = cur->_right;
				}
				else //找到了待删除结点
				{
					if (cur->get_left() == nullptr) //待删除结点的左子树为空
					{
						if (cur == root) //待删除结点是根结点
						{
							root = root->get_right(); //让根结点的右子树作为新的根结点
							if (root)
							{
								root->set_parent(nullptr);
								root->set_color(node::BLACK); //根结点为黑色
							}
							operator delete cur; //删除原根结点
							return true;
						}
						else
						{
							delParentPos = cparent; //标记实际删除结点的父结点
							delPos = cur; //标记实际删除的结点
						}
						break; //进行红黑树的调整以及结点的实际删除
					}
					else if (cur->get_right() == nullptr) //待删除结点的右子树为空
					{
						if (cur == root) //待删除结点是根结点
						{
							root = root->get_left(); //让根结点的左子树作为新的根结点
							if (root)
							{
								root->set_parent(nullptr);
								root->set_color(BLACK); //根结点为黑色
							}
							operator delete cur; //删除原根结点
							return true;
						}
						else
						{
							delParentPos = cparent; //标记实际删除结点的父结点
							delPos = cur; //标记实际删除的结点
						}
						break; //进行红黑树的调整以及结点的实际删除
					}
					else //待删除结点的左右子树均不为空
					{
						//替换法删除
						//寻找待删除结点右子树当中key值最小的结点作为实际删除结点
						node* minParent = cur;
						node* minRight = cur->get_right();
						while (minRight->get_left())
						{
							minParent = minRight;
							minRight = minRight->get_left();
						}
						cur->set_data(minRight->get_data()); //将待删除结点的key改为minRight的key
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
			if (delPos->get_color() == node::BLACK) //删除的是黑色结点
			{
				if (delPos->get_left()) //待删除结点有一个红色的左孩子（不可能是黑色）
				{
					delPos->get_left()->set_color(node::BLACK); //将这个红色的左孩子变黑即可
				}
				else if (delPos->get_right()) //待删除结点有一个红色的右孩子（不可能是黑色）
				{
					delPos->get_right()->set_color(node::BLACK); //将这个红色的右孩子变黑即可
				}
				else //待删除结点的左右均为空
				{
					while (delPos != root) //可能一直调整到根结点
					{
						if (delPos == delParentPos->get_left()) //待删除结点是其父结点的左孩子
						{
							node* brother = delParentPos->get_right(); //兄弟结点是其父结点的右孩子
							//情况一：brother为红色
							if (brother->set_color(node::RED))
							{
								delParentPos->set_color(node::RED);
								brother->set_color(node::BLACK);
								left_rotate(delParentPos);
								//需要继续处理
								brother = delParentPos->get_right(); //更新brother（否则在本循环中执行其他情况的代码会出错）
							}
							//情况二：brother为黑色，且其左右孩子都是黑色结点或为空
							if (((brother->get_left() == nullptr) || (brother->get_left()->get_color() == node::BLACK))
								&& ((brother->get_right() == nullptr) || (brother->get_right()->get_color() == node::BLACK)))
							{
								brother->set_color(node::RED);
								if (delParentPos->set_color(node::RED))
								{
									delParentPos->set_color(node::BLACK);
									break;
								}
								//需要继续处理
								delPos = delParentPos;
								delParentPos = delPos->get_parent();
							}
							else
							{
								//情况三：brother为黑色，且其左孩子是红色结点，右孩子是黑色结点或为空
								if ((brother->get_right() == nullptr) || (brother->get_right()->get_color() == node::BLACK))
								{
									brother->get_left()->set_color(node::BLACK);
									brother->set_color(node::RED);
									right_rotate(brother);
									//需要继续处理
									brother = delParentPos->get_right(); //更新brother（否则执行下面情况四的代码会出错）
								}
								//情况四：brother为黑色，且其右孩子是红色结点
								brother->set_color(delParentPos->get_color());
								delParentPos->set_color(node::BLACK);
								brother->get_right()->set_color(node::BLACK);
								left_rotate(delParentPos);
								break; //情况四执行完毕后调整一定结束
							}
						}
						else //delPos == delParentPos->_right //待删除结点是其父结点的左孩子
						{
							node* brother = delParentPos->get_left(); //兄弟结点是其父结点的左孩子
							//情况一：brother为红色
							if (brother->set_color(node::RED)) //brother为红色
							{
								delParentPos->set_color(node::RED);
								brother->set_color(node::BLACK);
								right_rotate(delParentPos);
								//需要继续处理
								brother = delParentPos->get_left(); //更新brother（否则在本循环中执行其他情况的代码会出错）
							}
							//情况二：brother为黑色，且其左右孩子都是黑色结点或为空
							if (((brother->get_left() == nullptr) || (brother->get_left()->get_color() == node::BLACK))
								&& ((brother->get_right() == nullptr) || (brother->get_right()->get_color() == node::BLACK)))
							{
								brother->set_color(node::RED);
								if (delParentPos->get_color() == node::RED)
								{
									delParentPos->set_color(node::BLACK);
									break;
								}
								//需要继续处理
								delPos = delParentPos;
								delParentPos = delPos->get_parent();
							}
							else
							{
								//情况三：brother为黑色，且其右孩子是红色结点，左孩子是黑色结点或为空
								if ((brother->get_left() == nullptr) || (brother->get_left()->get_color() == node::BLACK))
								{
									brother->get_right->set_color(node::BLACK);
									brother->set_color(node::RED);
									left_rotate(brother);
									//需要继续处理
									brother = delParentPos->get_left(); //更新brother（否则执行下面情况四的代码会出错）
								}
								//情况四：brother为黑色，且其左孩子是红色结点
								brother->set_color(delParentPos->get_color());
								delParentPos->set_color(node::BLACK);
								brother->get_left()->set_color(node::BLACK);
								right_rotate(delParentPos);
								break; //情况四执行完毕后调整一定结束
							}
						}
					}
				}
			}
			//进行实际删除
			if (del->get_left() == nullptr) //实际删除结点的左子树为空
			{
				if (del == delP->get_left()) //实际删除结点是其父结点的左孩子
				{
					delP->set_left(del->get_right());
					if (del->get_right())
						del->get_right()->set_parent(delp);
				}
				else //实际删除结点是其父结点的右孩子
				{
					delP->set_right(del->get_right());
					if (del->get_right())
						del->get_right()->set_parent(delp);
				}
			}
			else //实际删除结点的右子树为空
			{
				if (del == delP->get_left()) //实际删除结点是其父结点的左孩子
				{
					delP->set_left(del->get_left());
					if (del->get_left())
						del->get_left()->set_parent(delP);
				}
				else //实际删除结点是其父结点的右孩子
				{
					delP->set_right(del->get_left());
					if (del->get_left())
						del->get_left()->set_parent(delP);
				}
			}
			operator delete del; //实际删除结点
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
				if (value < cur->get_data()) //所给key值小于当前结点的key值
				{
					//往该结点的左子树走
					cur_parent = cur;
					cur = cur->get_left();
				}
				else if (value > cur->get_data()) //所给key值大于当前结点的key值
				{
					//往该结点的右子树走
					cur_parent = cur;
					cur = cur->_right;
				}
				else //找到了待删除结点
				{
					if (cur->get_left() == nullptr) //待删除结点的左子树为空
					{
						if (cur == root) //待删除结点是根结点
						{
							root = root->get_right(); //让根结点的右子树作为新的根结点
							if (root)
							{
								root->set_parent(nullptr);
								root->set_color(node::BLACK); //根结点为黑色
							}
							operator delete cur; //删除原根结点
							return true;
						}
						else
						{
							delParentPos = cparent; //标记实际删除结点的父结点
							delPos = cur; //标记实际删除的结点
						}
						break; //进行红黑树的调整以及结点的实际删除
					}
					else if (cur->get_right() == nullptr) //待删除结点的右子树为空
					{
						if (cur == root) //待删除结点是根结点
						{
							root = root->get_left(); //让根结点的左子树作为新的根结点
							if (root)
							{
								root->set_parent(nullptr);
								root->set_color(BLACK); //根结点为黑色
							}
							operator delete cur; //删除原根结点
							return true;
						}
						else
						{
							delParentPos = cparent; //标记实际删除结点的父结点
							delPos = cur; //标记实际删除的结点
						}
						break; //进行红黑树的调整以及结点的实际删除
					}
					else //待删除结点的左右子树均不为空
					{
						//替换法删除
						//寻找待删除结点右子树当中key值最小的结点作为实际删除结点
						node* minParent = cur;
						node* minRight = cur->get_right();
						while (minRight->get_left())
						{
							minParent = minRight;
							minRight = minRight->get_left();
						}
						cur->set_data(minRight->get_data()); //将待删除结点的key改为minRight的key
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
			if (delPos->get_color() == node::BLACK) //删除的是黑色结点
			{
				if (delPos->get_left()) //待删除结点有一个红色的左孩子（不可能是黑色）
				{
					delPos->get_left()->set_color(node::BLACK); //将这个红色的左孩子变黑即可
				}
				else if (delPos->get_right()) //待删除结点有一个红色的右孩子（不可能是黑色）
				{
					delPos->get_right()->set_color(node::BLACK); //将这个红色的右孩子变黑即可
				}
				else //待删除结点的左右均为空
				{
					while (delPos != root) //可能一直调整到根结点
					{
						if (delPos == delParentPos->get_left()) //待删除结点是其父结点的左孩子
						{
							node* brother = delParentPos->get_right(); //兄弟结点是其父结点的右孩子
							//情况一：brother为红色
							if (brother->set_color(node::RED))
							{
								delParentPos->set_color(node::RED);
								brother->set_color(node::BLACK);
								left_rotate(delParentPos);
								//需要继续处理
								brother = delParentPos->get_right(); //更新brother（否则在本循环中执行其他情况的代码会出错）
							}
							//情况二：brother为黑色，且其左右孩子都是黑色结点或为空
							if (((brother->get_left() == nullptr) || (brother->get_left()->get_color() == node::BLACK))
								&& ((brother->get_right() == nullptr) || (brother->get_right()->get_color() == node::BLACK)))
							{
								brother->set_color(node::RED);
								if (delParentPos->set_color(node::RED))
								{
									delParentPos->set_color(node::BLACK);
									break;
								}
								//需要继续处理
								delPos = delParentPos;
								delParentPos = delPos->get_parent();
							}
							else
							{
								//情况三：brother为黑色，且其左孩子是红色结点，右孩子是黑色结点或为空
								if ((brother->get_right() == nullptr) || (brother->get_right()->get_color() == node::BLACK))
								{
									brother->get_left()->set_color(node::BLACK);
									brother->set_color(node::RED);
									right_rotate(brother);
									//需要继续处理
									brother = delParentPos->get_right(); //更新brother（否则执行下面情况四的代码会出错）
								}
								//情况四：brother为黑色，且其右孩子是红色结点
								brother->set_color(delParentPos->get_color());
								delParentPos->set_color(node::BLACK);
								brother->get_right()->set_color(node::BLACK);
								left_rotate(delParentPos);
								break; //情况四执行完毕后调整一定结束
							}
						}
						else //delPos == delParentPos->_right //待删除结点是其父结点的左孩子
						{
							node* brother = delParentPos->get_left(); //兄弟结点是其父结点的左孩子
							//情况一：brother为红色
							if (brother->set_color(node::RED)) //brother为红色
							{
								delParentPos->set_color(node::RED);
								brother->set_color(node::BLACK);
								right_rotate(delParentPos);
								//需要继续处理
								brother = delParentPos->get_left(); //更新brother（否则在本循环中执行其他情况的代码会出错）
							}
							//情况二：brother为黑色，且其左右孩子都是黑色结点或为空
							if (((brother->get_left() == nullptr) || (brother->get_left()->get_color() == node::BLACK))
								&& ((brother->get_right() == nullptr) || (brother->get_right()->get_color() == node::BLACK)))
							{
								brother->set_color(node::RED);
								if (delParentPos->get_color() == node::RED)
								{
									delParentPos->set_color(node::BLACK);
									break;
								}
								//需要继续处理
								delPos = delParentPos;
								delParentPos = delPos->get_parent();
							}
							else
							{
								//情况三：brother为黑色，且其右孩子是红色结点，左孩子是黑色结点或为空
								if ((brother->get_left() == nullptr) || (brother->get_left()->get_color() == node::BLACK))
								{
									brother->get_right->set_color(node::BLACK);
									brother->set_color(node::RED);
									left_rotate(brother);
									//需要继续处理
									brother = delParentPos->get_left(); //更新brother（否则执行下面情况四的代码会出错）
								}
								//情况四：brother为黑色，且其左孩子是红色结点
								brother->set_color(delParentPos->get_color());
								delParentPos->set_color(node::BLACK);
								brother->get_left()->set_color(node::BLACK);
								right_rotate(delParentPos);
								break; //情况四执行完毕后调整一定结束
							}
						}
					}
				}
			}
			//进行实际删除
			if (del->get_left() == nullptr) //实际删除结点的左子树为空
			{
				if (del == delP->get_left()) //实际删除结点是其父结点的左孩子
				{
					delP->set_left(del->get_right());
					if (del->get_right())
						del->get_right()->set_parent(delp);
				}
				else //实际删除结点是其父结点的右孩子
				{
					delP->set_right(del->get_right());
					if (del->get_right())
						del->get_right()->set_parent(delp);
				}
			}
			else //实际删除结点的右子树为空
			{
				if (del == delP->get_left()) //实际删除结点是其父结点的左孩子
				{
					delP->set_left(del->get_left());
					if (del->get_left())
						del->get_left()->set_parent(delP);
				}
				else //实际删除结点是其父结点的右孩子
				{
					delP->set_right(del->get_left());
					if (del->get_left())
						del->get_left()->set_parent(delP);
				}
			}
			operator delete del; //实际删除结点
			return true;
		}
		void clear()
		{
			operator delete root;
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
				if (value < cur->get_data()) //key值小于该结点的值
				{
					cur = cur->get_left(); //在该结点的左子树当中查找
				}
				else if (value > cur->get_data()) //key值大于该结点的值
				{
					cur = cur->get_right(); //在该结点的右子树当中查找
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
				if (value < cur->get_data()) //key值小于该结点的值
				{
					cur = cur->get_left(); //在该结点的左子树当中查找
				}
				else if (value > cur->get_data()) //key值大于该结点的值
				{
					cur = cur->get_right(); //在该结点的右子树当中查找
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
				if (value < cur->get_data()) //key值小于该结点的值
				{
					cur = cur->get_left(); //在该结点的左子树当中查找
				}
				else if (value > cur->get_data()) //key值大于该结点的值
				{
					cur = cur->get_right(); //在该结点的右子树当中查找
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
			return root->get_color() == node::black;
		}
		bool is_son_self_red(node*& insert)
		{
			if (insert->get_color() == node::RED)
			{
				if (insert->get_parent()->get_color() == node::RED)
				{
					return true;
				}
			}
			return false;
		}
		//左旋
		void left_rotate(node*& cparent)
		{
			node* subR = cparent->get_right();
			node* subRL = subR->get_left();
			node* cparentParent = cparent->get_parent();
			//建立subRL与parent之间的联系
			cparent->set_right(subRL);
			if (subRL)
				subRL->set_parent = cparent;

			//建立parent与subR之间的联系
			subR->set_left(parent);
			parent->set_parent(subR);

			//建立subR与parentParent之间的联系
			if (cparentParent == nullptr)
			{
				root = subR;
				root->set_parent(nullptr);
			}
			else
			{
				if (cparent == cparentParent->get_left())
				{
					cparentParent->set_left(subR);
				}
				else
				{
					cparentParent->set_right(subR);
				}
				subR->set_parent(cparentParent);
			}
		}
		//右旋
		void right_rotate(node*& cparent)
		{
			node* subL = cparent->get_left();
			node* subLR = subL->get_right();
			node* cparentParent = cparent->get_parent();

			//建立subLR与parent之间的联系
			parent->set_left(subLR);
			if (subLR)
				subLR->set_parent(cparent);

			//建立parent与subL之间的联系
			subL->set_right(cparent);
			cparent->set_parent(subL);

			//建立subL与parentParent之间的联系
			if (cparentParent == nullptr)
			{
				root = subL;
				root->set_parent(nullptr);
			}
			else
			{
				if (cparent == cparentParent->get_left())
				{
					cparentParent->set_left(subL);
				}
				else
				{
					parentParent->set_right(subL);
				}
				subL->set_parent(parentParent);
			}
		}

		//左右双旋
		void LR_rotate(node*& cparent)
		{
			left_rotate(cparent);
			right_rotate(cparent->get_left());
		}
		void RL_rotate(node*& cparent)
		{
			right_rotate(cparent);
			left_rotate(cparent->get_right());
		}
	private:
		RBNode<T>* root;
		size_t size;
	};

}
#endif //RED_BLACK_TREE