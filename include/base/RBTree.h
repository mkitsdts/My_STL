#pragma once
#include "allocator/Allocator.h"

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
			node(value_type& value) :parent(nullptr), left(nullptr), right(nullptr), data(value_type()), color(BLACK)//���ڵ�
			{
			}
			node(node* parent_value, value_type& value) :parent(parent_value), left(nullptr), right(nullptr), data(value), color(RED)//��ͨ�ڵ�
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
			if (root == nullptr) //�������Ϊ�������������ֱ����Ϊ�����
			{
				root = new node(value);
			}
			//�ҵ�������λ��
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

			cur = new node(cur_parent,value); //��������ֵ����һ�����
			node* newnode = cur; //��¼��㣨���ں��򷵻�
			if (value < cur_parent->data)
			{
				//���뵽parent�����
				cur_parent->left = cur;
			}
			else
			{
				//���뵽parent���ұ�
				cur_parent->right = cur;
			}

			//�Ժ�������е���
			while (is_son_self_red(cur_parent))//�����ʹ�����ڵ��Ǻ�ɫ
			{
				node* cur_grandfather = cur_parent->parent; //parent�Ǻ�ɫ�����丸���һ������
				if (cur_parent == cur_grandfather->left) //parent��grandfather������
				{
					node* cur_uncle = cur_grandfather->right; //uncle��grandfather���Һ���
					if (cur_uncle && cur_uncle->color == RED) //uncle������Ϊ��
					{
						//��ɫ����
						cur_parent->color = BLACK;
						cur_uncle->color = BLACK;
						cur_grandfather->color = RED;

						//�������ϴ���
						cur = cur_grandfather;
						cur_parent = cur->parent;
					}
					else //uncleΪ��
					{
						//�������
						if (cur == cur_parent->left)
						{
							right_rotate(cur_grandfather); //�ҵ���
							//��ɫ����
							cur_grandfather->color = RED;
							cur_parent->color = BLACK;
						}
						//�������
						else //cur == parent->right
						{
							LR_rotate(cur_grandfather); //����˫��
							//��ɫ����
							cur_grandfather->color = RED;
							cur_parent->color = BLACK;
						}
						break; //������ת�󣬸������ĸ�����˺�ɫ������������Ͻ��д���
					}
				}
				else //parent��grandfather���Һ���
				{
					node* cur_uncle = cur_grandfather->left;
					if (cur_uncle && cur_uncle->color == RED)
					{
						//��ɫ����
						cur_uncle->color = BLACK;
						cur_parent->color = BLACK;
						cur_grandfather->color = RED;
						//�������ϴ���
						cur = cur_grandfather;
						cur_parent = cur->parent;
					}
					else
					{
						//�������
						if (cur == cur_parent->left)
						{
							RL_rotate(cur_grandfather); //����˫��

							//��ɫ����
							cur->color = BLACK;
							cur_grandfather->color = RED;
						}
						//�������
						else //cur == parent->right
						{
							left_rotate(cur_grandfather); //����
							//��ɫ����
							cur_grandfather->color = RED;
							cur_parent->color = BLACK;
						}
						break; //������ת�󣬸������ĸ�����˺�ɫ������������Ͻ��д���
					}
				}
			}
			root->color = BLACK; //��������ɫΪ��ɫ�����ܱ����һ����˺�ɫ����Ҫ��غ�ɫ��
		}
		void insert(const value_type& value)
		{
			if (root == nullptr) //�������Ϊ�������������ֱ����Ϊ�����
			{
				root = new node(value);
			}
			//�ҵ�������λ��
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

			cur = new node(cur_parent, value); //��������ֵ����һ�����
			node* newnode = cur; //��¼��㣨���ں��򷵻�
			if (value < cur_parent->data)
			{
				//���뵽parent�����
				cur_parent->left = cur;
			}
			else
			{
				//���뵽parent���ұ�
				cur_parent->right = cur;
			}

			//�Ժ�������е���
			while (is_son_self_red(cur_parent))//�����ʹ�����ڵ��Ǻ�ɫ
			{
				node* cur_grandfather = cur_parent->parent; //parent�Ǻ�ɫ�����丸���һ������
				if (cur_parent == cur_grandfather->left) //parent��grandfather������
				{
					node* cur_uncle = cur_grandfather->right; //uncle��grandfather���Һ���
					if (cur_uncle && cur_uncle->color == RED) //uncle������Ϊ��
					{
						//��ɫ����
						cur_parent->color = BLACK;
						cur_uncle->color = BLACK;
						cur_grandfather->color = RED;

						//�������ϴ���
						cur = cur_grandfather;
						cur_parent = cur->parent;
					}
					else //uncleΪ��
					{
						//�������
						if (cur == cur_parent->left)
						{
							right_rotate(cur_grandfather); //�ҵ���
							//��ɫ����
							cur_grandfather->color = RED;
							cur_parent->color = BLACK;
						}
						//�������
						else //cur == parent->right
						{
							LR_rotate(cur_grandfather); //����˫��
							//��ɫ����
							cur_grandfather->color = RED;
							cur_parent->color = BLACK;
						}
						break; //������ת�󣬸������ĸ�����˺�ɫ������������Ͻ��д���
					}
				}
				else //parent��grandfather���Һ���
				{
					node* cur_uncle = cur_grandfather->left;
					if (cur_uncle && cur_uncle->color == RED)
						{
							//��ɫ����
							cur_uncle->color = BLACK;
							cur_parent->color = BLACK;
							cur_grandfather->color = RED;
						//�������ϴ���
						cur = cur_grandfather;
						cur_parent = cur->parent;
						}
					else
					{
						//�������
						if (cur == cur_parent->left)
						{
							RL_rotate(cur_grandfather); //����˫��

							//��ɫ����
							cur->color = BLACK;
							cur_grandfather->color = RED;
						}
						//�������
						else //cur == parent->right
						{
							left_rotate(cur_grandfather); //����
							//��ɫ����
							cur_grandfather->color = RED;
							cur_parent->color = BLACK;
						}
						break; //������ת�󣬸������ĸ�����˺�ɫ������������Ͻ��д���
					}
				}
			}
			root->color = BLACK; //��������ɫΪ��ɫ�����ܱ����һ����˺�ɫ����Ҫ��غ�ɫ��
		}
		void insert(value_type&& value)
		{
			if (root == nullptr) //�������Ϊ�������������ֱ����Ϊ�����
			{
				root = new node(value);
			}
			//�ҵ�������λ��
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

			cur = new node(cur_parent, value); //��������ֵ����һ�����
			node* newnode = cur; //��¼��㣨���ں��򷵻�
			if (value < cur_parent->data)
			{
				//���뵽parent�����
				cur_parent->left = cur;
			}
			else
			{
				//���뵽parent���ұ�
				cur_parent->right = cur;
			}

			//�Ժ�������е���
			while (is_son_self_red(cur_parent))//�����ʹ�����ڵ��Ǻ�ɫ
			{
				node* cur_grandfather = cur_parent->parent; //parent�Ǻ�ɫ�����丸���һ������
				if (cur_parent == cur_grandfather->left) //parent��grandfather������
				{
					node* cur_uncle = cur_grandfather->right; //uncle��grandfather���Һ���
					if (cur_uncle && cur_uncle->color == RED) //uncle������Ϊ��
					{
						//��ɫ����
						cur_parent->color = BLACK;
						cur_uncle->color = BLACK;
						cur_grandfather->color = RED;

						//�������ϴ���
						cur = cur_grandfather;
						cur_parent = cur->parent;
					}
					else //uncleΪ��
					{
						//�������
						if (cur == cur_parent->left)
						{
							right_rotate(cur_grandfather); //�ҵ���
							//��ɫ����
							cur_grandfather->color = RED;
							cur_parent->color = BLACK;
						}
						//�������
						else //cur == parent->right
						{
							LR_rotate(cur_grandfather); //����˫��
							//��ɫ����
							cur_grandfather->color = RED;
							cur_parent->color = BLACK;
						}
						break; //������ת�󣬸������ĸ�����˺�ɫ������������Ͻ��д���
					}
				}
				else //parent��grandfather���Һ���
				{
					node* cur_uncle = cur_grandfather->left;
					if (cur_uncle && cur_uncle->color == RED)
						{
							//��ɫ����
							cur_uncle->color = BLACK;
							cur_parent->color = BLACK;
							cur_grandfather->color = RED;
						//�������ϴ���
						cur = cur_grandfather;
						cur_parent = cur->parent;
						}
					else
					{
						//�������
						if (cur == cur_parent->left)
						{
							RL_rotate(cur_grandfather); //����˫��

							//��ɫ����
							cur->color = BLACK;
							cur_grandfather->color = RED;
						}
						//�������
						else //cur == parent->right
						{
							left_rotate(cur_grandfather); //����
							//��ɫ����
							cur_grandfather->color = RED;
							cur_parent->color = BLACK;
						}
						break; //������ת�󣬸������ĸ�����˺�ɫ������������Ͻ��д���
					}
				}
			}
			root->color = BLACK; //��������ɫΪ��ɫ�����ܱ����һ����˺�ɫ����Ҫ��غ�ɫ��
		}

		bool erase(value_type& value)
		{
			//���ڱ���������
			node* cur_parent = nullptr;
			node* cur = root;
			//���ڱ��ʵ�ʵĴ�ɾ����㼰�丸���
			node* delParentPos = nullptr;
			node* delPos = nullptr;
			while (cur)
			{
				if (value < cur->data) //����keyֵС�ڵ�ǰ����keyֵ
				{
					//���ý�����������
					cur_parent = cur;
					cur = cur->left;
				}
				else if (value > cur->data) //����keyֵ���ڵ�ǰ����keyֵ
				{
					//���ý�����������
					cur_parent = cur;
					cur = cur->_right;
				}
				else //�ҵ��˴�ɾ�����
				{
					if (cur->left == nullptr) //��ɾ������������Ϊ��
					{
						if (cur == root) //��ɾ������Ǹ����
						{
							root = root->right; //�ø�������������Ϊ�µĸ����
							if (root)
							{
								root->parent = nullptr;
								root->color = BLACK; //�����Ϊ��ɫ
							}
							delete cur; //ɾ��ԭ�����
							return true;
						}
						else
						{
							delParentPos = cur_parent; //���ʵ��ɾ�����ĸ����
							delPos = cur; //���ʵ��ɾ���Ľ��
						}
						break; //���к�����ĵ����Լ�����ʵ��ɾ��
					}
					else if (cur->right == nullptr) //��ɾ������������Ϊ��
					{
						if (cur == root) //��ɾ������Ǹ����
						{
							root = root->left; //�ø�������������Ϊ�µĸ����
							if (root)
							{
								root->parent = nullptr;
								root->color = BLACK; //�����Ϊ��ɫ
							}
							delete cur; //ɾ��ԭ�����
							return true;
						}
						else
						{
							delParentPos = cur_parent; //���ʵ��ɾ�����ĸ����
							delPos = cur; //���ʵ��ɾ���Ľ��
						}
						break; //���к�����ĵ����Լ�����ʵ��ɾ��
					}
					else //��ɾ������������������Ϊ��
					{
						//�滻��ɾ��
						//Ѱ�Ҵ�ɾ���������������keyֵ��С�Ľ����Ϊʵ��ɾ�����
						node* minParent = cur;
						node* minRight = cur->right;
						while (minRight->left)
						{
							minParent = minRight;
							minRight = minRight->left;
						}
						cur->data = minRight->data; //����ɾ������key��ΪminRight��key
						delParentPos = minParent; //���ʵ��ɾ�����ĸ����
						delPos = minRight; //���ʵ��ɾ���Ľ��
						break; //���к�����ĵ����Լ�����ʵ��ɾ��
					}
				}
			}
			if (delPos == nullptr) //delPosû�б��޸Ĺ���˵��û���ҵ���ɾ�����
			{
				return false;
			}

			//��¼��ɾ����㼰�丸��㣨���ں���ʵ��ɾ����
			node* del = delPos;
			node* delP = delParentPos;

			//���������
			if (delPos->color == BLACK) //ɾ�����Ǻ�ɫ���
			{
				if (delPos->left) //��ɾ�������һ����ɫ�����ӣ��������Ǻ�ɫ��
				{
					delPos->left->color = BLACK; //�������ɫ�����ӱ�ڼ���
				}
				else if (delPos->right) //��ɾ�������һ����ɫ���Һ��ӣ��������Ǻ�ɫ��
				{
					delPos->right->color = BLACK; //�������ɫ���Һ��ӱ�ڼ���
				}
				else //��ɾ���������Ҿ�Ϊ��
				{
					while (delPos != root) //����һֱ�����������
					{
						if (delPos == delParentPos->left) //��ɾ��������丸��������
						{
							node* brother = delParentPos->right; //�ֵܽ�����丸�����Һ���
							//���һ��brotherΪ��ɫ
							if (brother->color = RED)
							{
								delParentPos->color = RED;
								brother->color = BLACK;
								left_rotate(delParentPos);
								//��Ҫ��������
								brother = delParentPos->right; //����brother�������ڱ�ѭ����ִ����������Ĵ���������
							}
							//�������brotherΪ��ɫ���������Һ��Ӷ��Ǻ�ɫ����Ϊ��
							if (((brother->left == nullptr) || (brother->left->color == BLACK))
								&& ((brother->right == nullptr) || (brother->right->color == BLACK)))
							{
								brother->color = RED;
								if (delParentPos->color = RED)
								{
									delParentPos->color = BLACK;
									break;
								}
								//��Ҫ��������
								delPos = delParentPos;
								delParentPos = delPos->get_parent();
							}
							else
							{
								//�������brotherΪ��ɫ�����������Ǻ�ɫ��㣬�Һ����Ǻ�ɫ����Ϊ��
								if ((brother->right == nullptr) || (brother->right->color == BLACK))
								{
									brother->left->color = BLACK;
									brother->color = RED;
									right_rotate(brother);
									//��Ҫ��������
									brother = delParentPos->right; //����brother������ִ����������ĵĴ���������
								}
								//����ģ�brotherΪ��ɫ�������Һ����Ǻ�ɫ���
								brother->colordelParentPos->color;
								delParentPos->color = BLACK;
								brother->right->color = BLACK;
								left_rotate(delParentPos);
								break; //�����ִ����Ϻ����һ������
							}
						}
						else //delPos == delParentPos->_right //��ɾ��������丸��������
						{
							node* brother = delParentPos->left; //�ֵܽ�����丸��������
							//���һ��brotherΪ��ɫ
							if (brother->color = RED) //brotherΪ��ɫ
							{
								delParentPos->color = RED;
								brother->color = BLACK;
								right_rotate(delParentPos);
								//��Ҫ��������
								brother = delParentPos->left; //����brother�������ڱ�ѭ����ִ����������Ĵ���������
							}
							//�������brotherΪ��ɫ���������Һ��Ӷ��Ǻ�ɫ����Ϊ��
							if (((brother->left == nullptr) || (brother->left->color == BLACK))
								&& ((brother->right == nullptr) || (brother->right->color == BLACK)))
							{
								brother->color = RED;
								if (delParentPos->color == RED)
								{
									delParentPos->color = BLACK;
									break;
								}
								//��Ҫ��������
								delPos = delParentPos;
								delParentPos = delPos->get_parent();
							}
							else
							{
								//�������brotherΪ��ɫ�������Һ����Ǻ�ɫ��㣬�����Ǻ�ɫ����Ϊ��
								if ((brother->left == nullptr) || (brother->left->color == BLACK))
								{
									brother->right->color = BLACK;
									brother->color = RED;
									left_rotate(brother);
									//��Ҫ��������
									brother = delParentPos->left; //����brother������ִ����������ĵĴ���������
								}
								//����ģ�brotherΪ��ɫ�����������Ǻ�ɫ���
								else if (!brother->color);
								{
									delParentPos->color = BLACK;
									brother->left->color = BLACK;
									right_rotate(delParentPos);
									break; //�����ִ����Ϻ����һ������
								}
							}
						}
					}
				}
			}
			//����ʵ��ɾ��
			if (del->left == nullptr) //ʵ��ɾ������������Ϊ��
			{
				if (del == delP->left) //ʵ��ɾ��������丸��������
				{
					delP->set_left(del->right);
					if (del->right)
						del->right->parent = delP;
				}
				else //ʵ��ɾ��������丸�����Һ���
				{
					delP->set_right(del->right);
					if (del->right)
						del->right->parent = delP;
				}
			}
			else //ʵ��ɾ������������Ϊ��
			{
				if (del == delP->left) //ʵ��ɾ��������丸��������
				{
					delP->set_left(del->left);
					if (del->left)
						del->left->parent = delP;
				}
				else //ʵ��ɾ��������丸�����Һ���
				{
					delP->set_right(del->left);
					if (del->left)
						del->left->parent = delP;
				}
			}
			free(del); //ʵ��ɾ�����
			return true;
		}
		bool erase(const value_type& value)
		{
			//���ڱ���������
			node* cur_parent = nullptr;
			node* cur = root;
			//���ڱ��ʵ�ʵĴ�ɾ����㼰�丸���
			node* delParentPos = nullptr;
			node* delPos = nullptr;
			while (cur)
			{
				if (value < cur->data) //����keyֵС�ڵ�ǰ����keyֵ
				{
					//���ý�����������
					cur_parent = cur;
					cur = cur->left;
				}
				else if (value > cur->data) //����keyֵ���ڵ�ǰ����keyֵ
				{
					//���ý�����������
					cur_parent = cur;
					cur = cur->_right;
				}
				else //�ҵ��˴�ɾ�����
				{
					if (cur->left == nullptr) //��ɾ������������Ϊ��
					{
						if (cur == root) //��ɾ������Ǹ����
						{
							root = root->right; //�ø�������������Ϊ�µĸ����
							if (root)
							{
								root->parent = nullptr;
								root->color = BLACK; //�����Ϊ��ɫ
							}
							free(cur); //ɾ��ԭ�����
							return true;
						}
						else
						{
							delParentPos = cur_parent; //���ʵ��ɾ�����ĸ����
							delPos = cur; //���ʵ��ɾ���Ľ��
						}
						break; //���к�����ĵ����Լ�����ʵ��ɾ��
					}
					else if (cur->right == nullptr) //��ɾ������������Ϊ��
					{
						if (cur == root) //��ɾ������Ǹ����
						{
							root = root->left; //�ø�������������Ϊ�µĸ����
							if (root)
							{
								root->parent = nullptr;
								root->color = BLACK; //�����Ϊ��ɫ
							}
							free(cur); //ɾ��ԭ�����
							return true;
						}
						else
						{
							delParentPos = cur_parent; //���ʵ��ɾ�����ĸ����
							delPos = cur; //���ʵ��ɾ���Ľ��
						}
						break; //���к�����ĵ����Լ�����ʵ��ɾ��
					}
					else //��ɾ������������������Ϊ��
					{
						//�滻��ɾ��
						//Ѱ�Ҵ�ɾ���������������keyֵ��С�Ľ����Ϊʵ��ɾ�����
						node* minParent = cur;
						node* minRight = cur->right;
						while (minRight->left)
						{
							minParent = minRight;
							minRight = minRight->left;
						}
						cur->data = minRight->data; //����ɾ������key��ΪminRight��key
						delParentPos = minParent; //���ʵ��ɾ�����ĸ����
						delPos = minRight; //���ʵ��ɾ���Ľ��
						break; //���к�����ĵ����Լ�����ʵ��ɾ��
					}
				}
			}
			if (delPos == nullptr) //delPosû�б��޸Ĺ���˵��û���ҵ���ɾ�����
			{
				return false;
			}

			//��¼��ɾ����㼰�丸��㣨���ں���ʵ��ɾ����
			node* del = delPos;
			node* delP = delParentPos;

			//���������
			if (delPos->color == BLACK) //ɾ�����Ǻ�ɫ���
			{
				if (delPos->left) //��ɾ�������һ����ɫ�����ӣ��������Ǻ�ɫ��
				{
					delPos->left->color = BLACK; //�������ɫ�����ӱ�ڼ���
				}
				else if (delPos->right) //��ɾ�������һ����ɫ���Һ��ӣ��������Ǻ�ɫ��
				{
					delPos->right->color = BLACK; //�������ɫ���Һ��ӱ�ڼ���
				}
				else //��ɾ���������Ҿ�Ϊ��
				{
					while (delPos != root) //����һֱ�����������
					{
						if (delPos == delParentPos->left) //��ɾ��������丸��������
						{
							node* brother = delParentPos->right; //�ֵܽ�����丸�����Һ���
							//���һ��brotherΪ��ɫ
							if (brother->color = RED)
							{
								delParentPos->color = RED;
								brother->color = BLACK;
								left_rotate(delParentPos);
								//��Ҫ��������
								brother = delParentPos->right; //����brother�������ڱ�ѭ����ִ����������Ĵ���������
							}
							//�������brotherΪ��ɫ���������Һ��Ӷ��Ǻ�ɫ����Ϊ��
							if (((brother->left == nullptr) || (brother->left->color == BLACK))
								&& ((brother->right == nullptr) || (brother->right->color == BLACK)))
							{
								brother->color = RED;
								if (delParentPos->color = RED)
								{
									delParentPos->color = BLACK;
									break;
								}
								//��Ҫ��������
								delPos = delParentPos;
								delParentPos = delPos->get_parent();
							}
							else
							{
								//�������brotherΪ��ɫ�����������Ǻ�ɫ��㣬�Һ����Ǻ�ɫ����Ϊ��
								if ((brother->right == nullptr) || (brother->right->color == BLACK))
								{
									brother->left->color = BLACK;
									brother->color = RED;
									right_rotate(brother);
									//��Ҫ��������
									brother = delParentPos->right; //����brother������ִ����������ĵĴ���������
								}
								//����ģ�brotherΪ��ɫ�������Һ����Ǻ�ɫ���
								brother->colordelParentPos->color;
								delParentPos->color = BLACK;
								brother->right->color = BLACK;
								left_rotate(delParentPos);
								break; //�����ִ����Ϻ����һ������
							}
						}
						else //delPos == delParentPos->_right //��ɾ��������丸��������
						{
							node* brother = delParentPos->left; //�ֵܽ�����丸��������
							//���һ��brotherΪ��ɫ
							if (brother->color = RED) //brotherΪ��ɫ
							{
								delParentPos->color = RED;
								brother->color = BLACK;
								right_rotate(delParentPos);
								//��Ҫ��������
								brother = delParentPos->left; //����brother�������ڱ�ѭ����ִ����������Ĵ���������
							}
							//�������brotherΪ��ɫ���������Һ��Ӷ��Ǻ�ɫ����Ϊ��
							if (((brother->left == nullptr) || (brother->left->color == BLACK))
								&& ((brother->right == nullptr) || (brother->right->color == BLACK)))
							{
								brother->color = RED;
								if (delParentPos->color == RED)
								{
									delParentPos->color = BLACK;
									break;
								}
								//��Ҫ��������
								delPos = delParentPos;
								delParentPos = delPos->get_parent();
							}
							else
							{
								//�������brotherΪ��ɫ�������Һ����Ǻ�ɫ��㣬�����Ǻ�ɫ����Ϊ��
								if ((brother->left == nullptr) || (brother->left->color == BLACK))
								{
									brother->get_right->color = BLACK;
									brother->color = RED;
									left_rotate(brother);
									//��Ҫ��������
									brother = delParentPos->left; //����brother������ִ����������ĵĴ���������
								}
								//����ģ�brotherΪ��ɫ�����������Ǻ�ɫ���
								else if(!brother->color)
								{
									delParentPos->color = BLACK;
									brother->left->color = BLACK;
									right_rotate(delParentPos);
									break; //�����ִ����Ϻ����һ������
								}
							}
						}
					}
				}
			}
			//����ʵ��ɾ��
			if (del->left == nullptr) //ʵ��ɾ������������Ϊ��
			{
				if (del == delP->left) //ʵ��ɾ��������丸��������
				{
					delP->set_left(del->right);
					if (del->right)
						del->right->parent = delP;
				}
				else //ʵ��ɾ��������丸�����Һ���
				{
					delP->set_right(del->right);
					if (del->right)
						del->right->parent = delP;
				}
			}
			else //ʵ��ɾ������������Ϊ��
			{
				if (del == delP->left) //ʵ��ɾ��������丸��������
				{
					delP->set_left(del->left);
					if (del->left)
						del->left->parent = delP;
				}
				else //ʵ��ɾ��������丸�����Һ���
				{
					delP->set_right(del->left);
					if (del->left)
						del->left->parent = delP;
				}
			}
			free(del); //ʵ��ɾ�����
			return true;
		}
		bool erase(value_type&& value)
		{
			//���ڱ���������
			node* cur_parent = nullptr;
			node* cur = root;
			//���ڱ��ʵ�ʵĴ�ɾ����㼰�丸���
			node* delParentPos = nullptr;
			node* delPos = nullptr;
			while (cur)
			{
				if (value < cur->data) //����keyֵС�ڵ�ǰ����keyֵ
				{
					//���ý�����������
					cur_parent = cur;
					cur = cur->left;
				}
				else if (value > cur->data) //����keyֵ���ڵ�ǰ����keyֵ
				{
					//���ý�����������
					cur_parent = cur;
					cur = cur->right;
				}
				else //�ҵ��˴�ɾ�����
				{
					if (cur->left == nullptr) //��ɾ������������Ϊ��
					{
						if (cur == root) //��ɾ������Ǹ����
						{
							root = root->right; //�ø�������������Ϊ�µĸ����
							if (root)
							{
								root->parent = nullptr;
								root->color = BLACK; //�����Ϊ��ɫ
							}
							free(cur); //ɾ��ԭ�����
							return true;
						}
						else
						{
							delParentPos = cur_parent; //���ʵ��ɾ�����ĸ����
							delPos = cur; //���ʵ��ɾ���Ľ��
						}
						break; //���к�����ĵ����Լ�����ʵ��ɾ��
					}
					else if (cur->right == nullptr) //��ɾ������������Ϊ��
					{
						if (cur == root) //��ɾ������Ǹ����
						{
							root = root->left; //�ø�������������Ϊ�µĸ����
							if (root)
							{
								root->parent = nullptr;
								root->color = BLACK; //�����Ϊ��ɫ
							}
							free(cur); //ɾ��ԭ�����
							return true;
						}
						else
						{
							delParentPos = cur_parent; //���ʵ��ɾ�����ĸ����
							delPos = cur; //���ʵ��ɾ���Ľ��
						}
						break; //���к�����ĵ����Լ�����ʵ��ɾ��
					}
					else //��ɾ������������������Ϊ��
					{
						//�滻��ɾ��
						//Ѱ�Ҵ�ɾ���������������keyֵ��С�Ľ����Ϊʵ��ɾ�����
						node* minParent = cur;
						node* minRight = cur->right;
						while (minRight->left)
						{
							minParent = minRight;
							minRight = minRight->left;
						}
						cur->data = minRight->data; //����ɾ������key��ΪminRight��key
						delParentPos = minParent; //���ʵ��ɾ�����ĸ����
						delPos = minRight; //���ʵ��ɾ���Ľ��
						break; //���к�����ĵ����Լ�����ʵ��ɾ��
					}
				}
			}
			if (delPos == nullptr) //delPosû�б��޸Ĺ���˵��û���ҵ���ɾ�����
			{
				return false;
			}

			//��¼��ɾ����㼰�丸��㣨���ں���ʵ��ɾ����
			node* del = delPos;
			node* delP = delParentPos;

			//���������
			if (delPos->color == BLACK) //ɾ�����Ǻ�ɫ���
			{
				if (delPos->left) //��ɾ�������һ����ɫ�����ӣ��������Ǻ�ɫ��
				{
					delPos->left->color = BLACK; //�������ɫ�����ӱ�ڼ���
				}
				else if (delPos->right) //��ɾ�������һ����ɫ���Һ��ӣ��������Ǻ�ɫ��
				{
					delPos->right->color = BLACK; //�������ɫ���Һ��ӱ�ڼ���
				}
				else //��ɾ���������Ҿ�Ϊ��
				{
					while (delPos != root) //����һֱ�����������
					{
						if (delPos == delParentPos->left) //��ɾ��������丸��������
						{
							node* brother = delParentPos->right; //�ֵܽ�����丸�����Һ���
							//���һ��brotherΪ��ɫ
							if (brother->color = RED)
							{
								delParentPos->color = RED;
								brother->color = BLACK;
								left_rotate(delParentPos);
								//��Ҫ��������
								brother = delParentPos->right; //����brother�������ڱ�ѭ����ִ����������Ĵ���������
							}
							//�������brotherΪ��ɫ���������Һ��Ӷ��Ǻ�ɫ����Ϊ��
							if (((brother->left == nullptr) || (brother->left->color == BLACK))
								&& ((brother->right == nullptr) || (brother->right->color == BLACK)))
							{
								brother->color = RED;
								if (delParentPos->color = RED)
								{
									delParentPos->color = BLACK;
									break;
								}
								//��Ҫ��������
								delPos = delParentPos;
								delParentPos = delPos->parent;
							}
							else
							{
								//�������brotherΪ��ɫ�����������Ǻ�ɫ��㣬�Һ����Ǻ�ɫ����Ϊ��
								if ((brother->right == nullptr) || (brother->right->color == BLACK))
								{
									brother->left->color = BLACK;
									brother->color = RED;
									right_rotate(brother);
									//��Ҫ��������
									brother = delParentPos->right; //����brother������ִ����������ĵĴ���������
								}
								//����ģ�brotherΪ��ɫ�������Һ����Ǻ�ɫ���
								brother->color = RED;
								delParentPos->color = BLACK;
								brother->right->color = BLACK;
								left_rotate(delParentPos);
								break; //�����ִ����Ϻ����һ������
							}
						}
						else //delPos == delParentPos->_right //��ɾ��������丸��������
						{
							node* brother = delParentPos->left; //�ֵܽ�����丸��������
							//���һ��brotherΪ��ɫ
							if (brother->color = RED) //brotherΪ��ɫ
							{
								delParentPos->color = RED;
								brother->color = BLACK;
								right_rotate(delParentPos);
								//��Ҫ��������
								brother = delParentPos->left; //����brother�������ڱ�ѭ����ִ����������Ĵ���������
							}
							//�������brotherΪ��ɫ���������Һ��Ӷ��Ǻ�ɫ����Ϊ��
							if (((brother->left == nullptr) || (brother->left->color == BLACK))
								&& ((brother->right == nullptr) || (brother->right->color == BLACK)))
							{
								brother->color = RED;
								if (delParentPos->color == RED)
								{
									delParentPos->color = BLACK;
									break;
								}
								//��Ҫ��������
								delPos = delParentPos;
								delParentPos = delPos->parent;
							}
							else
							{
								//�������brotherΪ��ɫ�������Һ����Ǻ�ɫ��㣬�����Ǻ�ɫ����Ϊ��
								if ((brother->left == nullptr) || (brother->left->color == BLACK))
								{
									brother->right->color = BLACK;
									brother->color = RED;
									left_rotate(brother);
									//��Ҫ��������
									brother = delParentPos->left; //����brother������ִ����������ĵĴ���������
								}
								//����ģ�brotherΪ��ɫ�����������Ǻ�ɫ���
								else if(!brother->color);
								{
									delParentPos->color = BLACK;
									brother->left->color = BLACK;
									right_rotate(delParentPos);
									break; //�����ִ����Ϻ����һ������
								}
							}
						}
					}
				}
			}
			//����ʵ��ɾ��
			if (del->left == nullptr) //ʵ��ɾ������������Ϊ��
			{
				if (del == delP->left) //ʵ��ɾ��������丸��������
				{
					delP->left = (del->right);
					if (del->right)
						del->right->parent = delP;
				}
				else //ʵ��ɾ��������丸�����Һ���
				{
					delP->right = (del->right);
					if (del->right)
						del->right->parent = delP;
				}
			}
			else //ʵ��ɾ������������Ϊ��
			{
				if (del == delP->left) //ʵ��ɾ��������丸��������
				{
					delP->left = (del->left);
					if (del->left)
						del->left->parent = delP;
				}
				else //ʵ��ɾ��������丸�����Һ���
				{
					delP->right = (del->left);
					if (del->left)
						del->left->parent = delP;
				}
			}
			free(del); //ʵ��ɾ�����
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
				if (value < cur->data) //keyֵС�ڸý���ֵ
				{
					cur = cur->left; //�ڸý������������в���
				}
				else if (value > cur->data) //keyֵ���ڸý���ֵ
				{
					cur = cur->right; //�ڸý������������в���
				}
				else //�ҵ���Ŀ����
				{
					return cur; //���ظý��
				}
			}
			return nullptr; //����ʧ��
		}
		node* find(value_type& value)
		{
			node* cur = root;
			while (cur)
			{
				if (value < cur->data) //keyֵС�ڸý���ֵ
				{
					cur = cur->left; //�ڸý������������в���
				}
				else if (value > cur->data) //keyֵ���ڸý���ֵ
				{
					cur = cur->right; //�ڸý������������в���
				}
				else //�ҵ���Ŀ����
				{
					return cur; //���ظý��
				}
			}
			return nullptr; //����ʧ��
		}
		node* find(value_type&& value)
		{
			node* cur = root;
			while (cur)
			{
				if (value < cur->data) //keyֵС�ڸý���ֵ
				{
					cur = cur->left; //�ڸý������������в���
				}
				else if (value > cur->data) //keyֵ���ڸý���ֵ
				{
					cur = cur->right; //�ڸý������������в���
				}
				else //�ҵ���Ŀ����
				{
					return cur; //���ظý��
				}
			}
			return nullptr; //����ʧ��
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
		//����
		void left_rotate(node*& cparent)
		{
			node* subR = cparent->right;
			node* subRL = subR->left;
			node* cparentParent = cparent->parent;
			//����subRL��parent֮�����ϵ
			cparent->right = subRL;
			if (subRL)
				subRL->parent = cparent;

			//����parent��subR֮�����ϵ
			subR->left = (cparent);
			cparent->parent = subR;

			//����subR��parentParent֮�����ϵ
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
		//����
		void right_rotate(node*& cparent)
		{
			node* subL = cparent->left;
			node* subLR = subL->right;
			node* cparentParent = cparent->parent;

			//����subLR��parent֮�����ϵ
			cparent->left = subLR;
			if (subLR)
				subLR->parent = cparent;

			//����parent��subL֮�����ϵ
			subL->right = cparent;
			cparent->parent = subL;

			//����subL��parentParent֮�����ϵ
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

		//����˫��
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