class Context_manager{
    public:
        void order(std::string id, int& out_reg);
        std::pair<unsigned int, unsigned int> order(std::string id1, std::string id2);
        void new_scope();
        void del_scope();
        void new_frame();
        void get_to_reg(std::string id, unsigned int reg);
        unsigned int get_reg(unsigned int reg);
}