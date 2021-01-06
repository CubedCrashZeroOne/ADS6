// C++ iostream library.
#include <iostream>
#include <ctime>
#include <string>


using namespace std;

struct node {
	// Value stored in the node.
	int value;
	// Pointer to anti-derived node.
	node* prev;
	// Pointers to derived nodes.
	node* left, * right;
	// To see if it's a left or a right branch
	char side;
};

node* new_node(int temp_value, node* root, char side) {
	node* temp_node = new node;
	temp_node->value = temp_value;
	temp_node->prev = root;
	temp_node->side = side;
	// Set the value of the parameter given TO node value.
	temp_node->left = temp_node->right = NULL;
	// Node pointers null by default.
	return temp_node;
}

// Each element in a new line, spaces included.
void output_astree(node* root, int index = 0) {
	index++;
	if (root->left != NULL) {
		output_astree(root->left, index);
	}
	for (int i = 0; i < index; i++) {
		cout << "]]";
	}
	printf("%3d\n", root->value);

	if (root->right != NULL) {
		output_astree(root->right, index);
	}
}

// Output in ascending order.
void output_ascend(node* root) {
	if (root->left != NULL) {
		output_ascend(root->left);
	}
	cout << root->value << " ";

	if (root->right != NULL) {
		output_ascend(root->right);
	}

}

// Output in descending order.
void output_descend(node* root) {
	if (root->right != NULL) {
		output_descend(root->right);
	}
	cout << root->value << " ";

	if (root->left != NULL) {
		output_descend(root->left);
	}

}

void delete_remains(node* root) {
	if (root->left != NULL) {
		delete_remains(root->left);
	}
	if (root->right != NULL) {
		delete_remains(root->right);
	}
	delete root;
}

// Ответственный: Гусин
// The function for searching a given element
node* locate(node* root, int number) {
	if (root == NULL || root->value == number) return root;
	else if (root->value > number) root = locate(root->left, number);
	else root = locate(root->right, number);
	return root;
}

// Ответственный: Макогон
node* right_min(node* root){
	while (root->left != NULL) {
		root = root->left;
	}
	return root;
}

node* left_max(node* root) {
	while (root->right != NULL) {
		root = root->right;
	}
	return root;
}

// Ответственный: Шабай
// Deletion and Replacement.
void del_rep(node** root, node* del, node* rep = NULL) {


	switch (del->side)
	{
	case 'L': 
		del->prev->left = rep;
		break;
	case 'R': 
		del->prev->right = rep;
		break;
	case 'N': 
		*root = rep;
		break;
	}

	if (rep == NULL) return;
	
	switch (rep->side) {
	case 'L': {
		rep->prev->left = rep->right;
		if (rep->right != NULL) {
			rep->right->prev = rep->prev;
			rep->right->side = rep->side;
		}
		rep->side = del->side;
		rep->right = del->right;
		if (rep->right != NULL) rep->right->prev = rep;
		if (rep->prev != del) {
			rep->left = del->left;
			if (rep->left != NULL) rep->left->prev = rep;
		}
		rep->prev = del->prev;
		break;
	}
	case 'R': {
		rep->prev->right = rep->left;
		if (rep->left != NULL) {
			rep->left->prev = rep->prev;
			rep->left->side = rep->side;
		}
		rep->side = del->side;
		if (rep->prev != del) {
			rep->right = del->right;
			if (rep->right != NULL) rep->right->prev = rep;
		}
		rep->left = del->left;
		if (rep->left != NULL) rep->left->prev = rep;
		rep->prev = del->prev;
	}
	}
	delete del;
}

int main() {
	int start_array[10];

	srand(time(NULL));


	for (int i = 0; i < 10; i++) {
		start_array[i] = rand() % 41 - 20;
		cout << start_array[i] << " ";
	}
	cout << "  Repeating numbers will be omitted." << endl;

	node* root = new_node(start_array[0], NULL, 'N');


	for (int i = 1; i < 10; i++) {
		node* temp_node = root;
		while (1) {

			// If greater than current node, go right. Otherwise go left.
			if (start_array[i] > temp_node->value) {
				if (temp_node->right == NULL) {
					temp_node->right = new_node(start_array[i], temp_node, 'R');
					break;
				}
				temp_node = temp_node->right;
			}
			else if (start_array[i] < temp_node->value) {
				if (temp_node->left == NULL) {
					temp_node->left = new_node(start_array[i], temp_node, 'L');
					break;
				}
				temp_node = temp_node->left;
			}
			else break;
		}
	}

	int choice;
	int delet_number;
	node* to_delete, * to_replace;

	while (true) {
		cout << "Input the action you want to do (\'9\' for the list of actions): ";
		cin >> choice;

		switch (choice) {
		case 1: {
			if (root == NULL) {
				cout << endl << "You have deleted the whole tree. Program shutdown." << endl;
				system("pause");
				return 0;
			}
			cout << endl << "1. Not beautiful output as a tree:" << endl;
			output_astree(root);
			break;
		}
		case 2: {
			if (root == NULL) {
				cout << endl << "You have deleted the whole tree. Program shutdown." << endl;
				system("pause");
				return 0;
			}
			cout << endl << "2. Output in ascending order:" << endl;
			output_ascend(root);
			cout << endl;
			break;
		}
		case 3: {
			if (root == NULL) {
				cout << endl << "You have deleted the whole tree. Program shutdown." << endl;
				system("pause");
				return 0;
			}
			cout << endl << "3. Output in descending order:" << endl;
			output_descend(root);
			cout << endl;
			break;
		}
		case 4: {
			cout << endl << "4. Node Deletion:" << endl;
			cin >> delet_number;
			node* locat = locate(root, delet_number);
			node* replac;
			node** root_ptr = &root;
			if (locat == NULL) cout << "There is no such element" << endl;
			else {
				if (locat->right != NULL) {
					replac = right_min(locat->right);
					del_rep(root_ptr, locat, replac);
					cout << "Deletion successful!\a" << endl;
				}
				else if (locat->left != NULL) {
					replac = left_max(locat->left);
					del_rep(root_ptr, locat, replac);
					cout << "Deletion successful!\a" << endl;
				}
				else {
					del_rep(root_ptr, locat);
					cout << "Deletion successful!\a" << endl;
				}
			}
			break;
		}
		case 9: cout << endl << "1. Not beautiful output as a tree:" << endl
			<< "2. Output in ascending order:" << endl
			<< "3. Output in descending order:" << endl
			<< "4. Deleting a node from the tree:" << endl
			<< "0. Exit." << endl << endl;
			break;
		case 0: return 0;
		}
	}
}