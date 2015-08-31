struct TreeNode {
	int number;
	TreeNode* left;
	TreeNode* right;
	
	TreeNode(int n) {
		number = n;
		left = right = nullptr;
	}

	static void destroy(TreeNode* node) {
		if (node) {
			destroy(node->left);
			destroy(node->right);
			delete node;
		}
	}
};

