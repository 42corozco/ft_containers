/*	
	REDBLACK online
	- https://www.cs.usfca.edu/~galles/visualization/RedBlack.html ->

	doc
	- https://www.geeksforgeeks.org/red-black-tree-set-1-introduction-2/
	- https://programmerclick.com/article/5969958849/				en espanol
	- https://www.programiz.com/dsa/red-black-tree					la mejor que vi, codigo incluido


	colors
	- http://jafrog.com/2013/11/23/colors-in-terminal.html
*/

#ifndef REDBLACK_HPP
# define REDBLACK_HPP

#include <iostream>

# define C_RED		"\e[31m"
# define C_BLACK	"\e[30m\e[47m"
# define C_RESET	"\e[0m"

namespace ft
{
	enum	Color {BLACK, RED};

	template<class T>
	struct	Node
	{
		T				data;
		struct Node		*padre;
		struct Node		*izquierda;
		struct Node		*derecha;
		Color			color;
		//se usa para poder usar el construct de allocator
		Node (T data, Node* padre, Node *izquierda, Node *derecha, Color color):data(data), padre(padre), izquierda(izquierda), derecha(derecha), color(color){}
	};

	template<class Key, class Value, class KeyOfValue, class Compare = std::less<Key>, class Alloc = std::allocator<Node<Value> > >
	class	RedBlack
	{
		public:
		typedef Value				value_type;
		typedef Key					key_type;
		typedef Alloc				allocator_type;
		typedef Compare				value_compare;
		typedef Node<value_type>	node_type;
		typedef Node<value_type>*	node_ptr;
		typedef std::size_t			size_type;

		//constructor
		RedBlack(const value_compare &comp = value_compare(), const allocator_type alloc = allocator_type()):
		_comp(comp), _size(0),_alloc(alloc)
		{
			// construction of leaf _nill (_TNULL)
			_TNULL = _alloc.allocate(1);
			_root = _TNULL;
			_alloc.construct(_TNULL, node_type(value_type(), NULL, NULL,NULL, BLACK)); // se contrulle de primero la cabeza de color negra
		}

		virtual			~RedBlack()
		{
			clear_recusive(_root);
			_root = _TNULL;
			_alloc.destroy(_TNULL);
			_alloc.deallocate(_TNULL, 1);
		}

		node_ptr	getRoot(void) const{ return _root;}
		size_type	getSize(void) const{ return _size;}
		node_ptr	getNill(void) const{ return _TNULL;}
		size_type	max_size(void) const {return _alloc.max_size();}

		//El valor mínimo de nani es el nodo más a la izquierda
		node_ptr		min(void) const
		{
			return min(_root);
		}

		node_ptr		min(node_ptr node) const
		{
			if(node == _TNULL)
				return _root;
			while(node->izquierda != _TNULL)
				node = node->izquierda;
			return node;
		}

		node_ptr		max(void) const
		{
			return max(_root);
		}

		node_ptr		max(node_ptr node) const
		{
			if(node == _TNULL)
				return _root;
			while(node->derecha != _TNULL)
				node = node->derecha;
			return node;
		}

		// inserta la key y ordena el arbol
		bool			insert(const value_type &data)
		{
			node_ptr	new_node;
			new_node = _alloc.allocate(1);
			_alloc.construct(new_node, node_type(data, NULL, _TNULL,_TNULL,RED));
			node_ptr	y = NULL;
			node_ptr	x = _root;
			while (x !=_TNULL)
			{
				y = x;
				if(_comp(KeyOfValue()(new_node->data), KeyOfValue()(x->data))) //comparar con la data con la funcion compare dentro del KeyOfValue 
					x = x->izquierda; // el nuevo nodo debe estar a la izquieda del arbol
				else if(_comp(KeyOfValue()(x->data), KeyOfValue()(new_node->data)))
					x = x->derecha;		//si el nuevo es en el lado de la derecha
				else
				{
					// no equal key so delete it
					_alloc.destroy(new_node);
					_alloc.deallocate(new_node, 1);
					return false;
				}
			}
			// y es padre de x, seria un lugar libre
			new_node->padre = y;
			if(!y)
				_root = new_node;   //si y existe, quedaria como el root 
			else if(_comp(KeyOfValue()(new_node->data), KeyOfValue()(y->data)))
				y->izquierda = new_node;
			else
				y->derecha = new_node;
			_size++;
			//si el nuevo nodo es un nodo ruta, se vuelve negro y regresa
			if(!new_node->padre)
			{
				new_node->color = BLACK;
				return true;
			}

			//si el abuelo es nulo
			if(!new_node->padre->padre)
				return true;
			//si el padre es negro, no se hace nada
			if(new_node->padre->color == BLACK)
				return true;
			//se balancea el arbol para terminar
			balance(new_node);
			return true;
		}

		value_type		&get_data(node_ptr node = NULL) const
		{
			if(!node)
				node = _root;
			return (node->data);
		}

		int				height(node_ptr node = NULL) const
		{
			if(!node)
				node = _root;
			int hl = 0,hr = 0,h = 0 ;
			if( !node || node == _TNULL)
				h = 0;
			else
			{
				hl = height(node->izquierda);
				hr = height(node->derecha);

				h = (hl > hr ? hl:hr) + 1;
			}
			return h;
		}

		void			print(bool const memory = false) const
		{
			print(memory, _root, "", true);
		}

		bool			deleteNode(const key_type &key)
		{
			node_ptr nodo_delete, nodo_control, _tmp;
			Color		saved_color;
			bool		leaf;

			nodo_delete = search(key);
			if (nodo_delete == _TNULL) //si no esta
				return false;
			leaf = is_leaf(nodo_delete);
			saved_color = nodo_delete->color;
			//si el nodo a suprimir tiene uno o no tiene hijos (_NILL), se inyectan estos al pade
			if(nodo_delete->izquierda == _TNULL)
			{// solo hijo de la derecha, igual para el de despues
				nodo_control = nodo_delete->derecha;
				graft(nodo_delete, nodo_delete->derecha);
			}
			else if(nodo_delete->derecha == _TNULL)
			{
				nodo_control = nodo_delete->izquierda;
				graft(nodo_delete, nodo_delete->izquierda);
			}
			else
			{
				// si tiene dos hijos
				//se reemplaza por el mínimo de su rama derecha (sucesor)
				_tmp = min(nodo_delete->derecha); //busca el min en la rama hijo de la derecha
				saved_color = _tmp->color;
				nodo_control = _tmp->derecha;  //para controlar la rama derecha
				if (_tmp->padre == nodo_delete)//el minimo es
					nodo_control->padre = _tmp;
				else
				{
					graft(_tmp, _tmp->derecha);
					_tmp->derecha = nodo_delete->derecha;   // ahora es de la derecha de tmp 
					_tmp->derecha->padre = _tmp;     //la antigua derecha de nodo_delete
				}
				graft(nodo_delete, _tmp);
				_tmp->izquierda = nodo_delete->izquierda; //ahora es el de la izquierda 
				_tmp->izquierda->padre = _tmp;  //antigua izquieda de nodo_delete

				_tmp->color = nodo_delete->color; // tmp coge el color de nodo_delete 
			}
			_alloc.destroy(nodo_delete);        // borrando el nodo_delete
			_alloc.deallocate(nodo_delete, 1);
			_size--;
			if(!leaf && saved_color == BLACK)
				RN_correction(nodo_control);
			return true;
		}

		node_ptr		search(const key_type &key) const
		{
			return  search(_root, key);
		}

		static int		max_depth(node_ptr n)
		{
			if (!n) return 0;
			return 1 + std::max(max_depth(n->izquierda), max_depth(n->derecha));
		}

		void			swap(RedBlack &tree)
		{
			node_ptr		tmp_root, tmp_TNULL;
			value_compare	tmp_comp;
			size_type		tmp_size;
			allocator_type	tmp_alloc;

			tmp_root = _root;
			tmp_TNULL = _TNULL;
			tmp_comp = _comp;
			tmp_size = _size;
			tmp_alloc = _alloc;

			this->_root = tree._root;
			this->_TNULL = tree._TNULL;
			this->_comp = tree._comp;
			this->_size = tree._size;
			this->_alloc = tree._alloc;

			tree._root = tmp_root;
			tree._TNULL = tmp_TNULL;
			tree._comp = tmp_comp;
			tree._size = tmp_size;
			tree._alloc = tmp_alloc;
		}
		private:
		node_ptr			_root;
		node_ptr			_TNULL;
		value_compare		_comp;
		size_type			_size;
		allocator_type		_alloc;

		node_ptr	search(node_ptr node, const key_type &key) const
		{
			if (node == _TNULL)
				return _TNULL;
			if (key == KeyOfValue()(node->data))
				return node;
			if (_comp(key, KeyOfValue()(node->data)))
				return (search(node->izquierda, key));
			else
				return (search(node->derecha, key));
		}

		void		rotation_izquierda(node_ptr  x)
		{
			node_ptr y = x->derecha; // y hijo derecho de x
				// y viejo hijo de la derecha, x el nuevo de la izquirda
			x->derecha = y->izquierda;
			if (y->izquierda != _TNULL)
				y->izquierda->padre = x;
			y->padre = x->padre; //el padre de x se vuelveel padre de y
			if (!x->padre)
				this->_root = y;
			else if (la_izquierda(x))    // x en la derecha o izquierda? 
				x->padre->izquierda = y; 
			else
				x->padre->derecha = y;
			y->izquierda = x; // x se vuelve el hijo de la izquierda
			x->padre = y;
		}

		void		rotation_derecha(node_ptr x)
		{
			node_ptr y = x->izquierda;

			x->izquierda = y->derecha;
			if (y->derecha != _TNULL)
				y->derecha->padre = x;
			y->padre = x->padre;
			if (!x->padre)
				this->_root = y;
			else if (la_derecha(x))
				x->padre->derecha = y;
			else
				x->padre->izquierda = y;
			y->derecha = x;
			x->padre = y;
		}

		void		balance(node_ptr new_node)
		{
			while(new_node->padre->color == RED) //mientras que el padre sea de color rojo
			{
				if (new_node == _root)//si el padre es rojo, salimos
					break;
				//verificar si el tio es rojo. 
				node_ptr    u;
				u = _uncle(new_node);
				if(u->color == RED) //si el tio es rojo, el abuelo, se vuelve rojo, el tio y el padre se vuelven negro
				{
					new_node->padre->padre->color = RED;
					u->color = BLACK;
					new_node->padre->color = BLACK;
					new_node = new_node->padre->padre;
				}
				else
				{
					//si el tio es negro
					if (la_derecha(new_node->padre))
					{
						//el padre esta a la derecha del abuelo
						if(la_izquierda(new_node))
						{
							// newNode el hijo de la izquierda
							new_node = new_node->padre;
							rotation_derecha(new_node);
						}
						new_node->padre->color = BLACK;
						new_node->padre->padre->color = RED;
						rotation_izquierda(new_node->padre->padre);
					}
					else if (la_izquierda(new_node->padre))
					{
						//el padre esta a la izquieda del abuelo
						if (la_derecha(new_node))
						{
							//new_node hijo de la derecha
							new_node = new_node->padre;
							rotation_izquierda(new_node);
						}
						new_node->padre->color = BLACK;
						new_node->padre->padre->color = RED;
						rotation_derecha(new_node->padre->padre);
					}
				}
				if(new_node == _root)
					break;
			}
			_root->color = BLACK;
		}

		static node_ptr	_uncle(node_ptr node)
		{
			node_ptr    p = node->padre;
			if (!p->padre)   //si no tiene abuelo
				return (NULL);       //no seria tio
			return (_brother(p));
		}

		static node_ptr	_brother(node_ptr node)
		{
			node_ptr    p = node->padre;
			if (!p)  //si no hay padre, no hay hermano.
				return NULL;
			if (node == p->izquierda)
				return p->derecha;
			else
				return p->izquierda;
		}

		static bool    la_izquierda(node_ptr node) { return (node == node->padre->izquierda); }
		static bool    la_derecha(node_ptr node) { return (node == node->padre->derecha); }

		bool			is_leaf(node_ptr node) const { return (node->izquierda == _TNULL && node->derecha == _TNULL); }

		/*clear*/
		void			clear_recusive(node_ptr const &node)
		{
			if (node == _TNULL)
				return;//parar lo recursivo
			clear_recusive(node->izquierda);
			clear_recusive(node->derecha);

			_alloc.destroy(node);
			_alloc.deallocate(node, 1);
			_size--;
		}

		void			graft(node_ptr a, node_ptr b) //inyectar b en lado de a
		{
			node_ptr    p = a->padre;
			if(!p)
				_root = b;
			else if(la_izquierda(a))
				p->izquierda = b;
			else
				p->derecha = b;
			b->padre = p;
		}

		void			RN_correction(node_ptr node)
		{
			while(node != _root && node->color == BLACK)
			{
				node_ptr    brother = _brother(node);
				if(la_izquierda(node))
				{
					if (brother->color == RED) //1
					{
						brother->color = BLACK;
						node->padre->color = RED;
						rotation_izquierda(node->padre);
						brother = node->padre->derecha;
					}

					if(brother->izquierda->color == BLACK && brother->derecha->color == BLACK) // los dos hijos del hermano son negros
					{ //2
						brother->color = RED;   //cambiarlos de color, controlando al padre volviendolo negro
						node = node->padre;
					}
					else    //si almenos un hijo es rojo
					{
						if(brother->derecha->color == BLACK)
						{
							//3
							brother->izquierda->color = BLACK;
							node->color = RED;
							rotation_derecha(node);
							brother = node->padre->derecha;
						}//4
						brother->color = node->padre->color;
						node->padre->color = BLACK;
						brother->derecha->color = BLACK;
						rotation_izquierda(node->padre);
						node = _root;
						break;
					}
				}
				else
				{
					if (brother->color == RED)
					{
						brother->color = BLACK;
						node->padre->color = RED;
						rotation_derecha(node->padre);
						brother = node->padre->izquierda;
					}

					if (brother->izquierda->color == BLACK && brother->derecha->color == BLACK)
					{
						brother->color = RED;
						node = node->padre;
					}
					else
					{
						if(brother->izquierda->color == BLACK)
						{
							brother->derecha->color = BLACK;
							brother->color = RED;
							rotation_izquierda(node);
							brother = node->padre->izquierda;
						}
						brother->color = node->padre->color;
						node->padre->color = BLACK;
						brother->izquierda->color = BLACK;
						rotation_derecha(node->padre);
						node = _root;
						break;
					}
				}
			}
			node->color = BLACK;
		}

		void print(bool memory, node_ptr root, std::string indent="", bool last=true) const
		{ 
			if (root != _TNULL)
			{
				std::cout << indent;
				if (last)
				{
					std::cout << "R----";
					indent += "     ";
				}
				else
				{
					std::cout << "L----";
					indent += "|    ";
				}
				std::string sColor = root->color? C_RED:C_BLACK;
				std::cout << sColor << KeyOfValue()(root->data) << C_RESET;
				if(memory)
					std::cout << " " <<&root;
				std::cout << std::endl;
				print(memory, root->izquierda, indent, false);
				print(memory, root->derecha, indent, true);
			}
		}
    };
}

#endif