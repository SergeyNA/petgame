SDL_Rect tree_viewport = {0, 80, SCREEN_WIDTH / 3, SCREEN_HEIGHT - 80};

WrapTexture close_branch;
WrapTexture open_branch;

std::pair<int, int> tree_render_pos[static_cast<int> ((SCREEN_HEIGHT - 80) / 25) + 1];
int tree_render_pos_index;
int research_index = -1;

struct Node
{
private:
    int *children;
    WrapTexture name_pic;
    WrapTexture descr_text;
    std::pair<int, int> *requirements;
    int req_count;
    int *cost;
    int index_in_technology;
public:
    int children_count;
    bool opened;
    int lvl;
    std::string name;
    int research_progress;
    int max_progress;
    void init(std::string tech_name, int index, int deep, int max_prog, int *price)
    {
        name = tech_name;
        name_pic.loadFromRenderedText(tech_name, YELLOW, 0);
        descr_text.loadFromRenderedText(tech_name+" "+"max level: "+toString(max_prog), BLACK, 3, true, SCREEN_WIDTH / 3 - 25); // todo: change tech descr
        lvl = deep;
        max_progress = max_prog;
        opened = false;
        research_progress = 0;
        req_count = 0;
        children_count = 0;
        cost = price;
        index_in_technology = index;
        //std::cout<<name<<" "<<index<<" "<<lvl<<std::endl;
    }
    void setChildren(int *chi, int num)
    {
        children = chi;
        children_count = num;
    }
    void setRequirements(std::pair<int, int> *chi, int num)
    {
        requirements = chi;
        req_count = num;
    }
    void render_descr()
    {
        descr_text.render(15, 65);
    }
    bool isResearchable()
    {
        if(research_progress < max_progress && science_points >= cost[research_progress])
            return true; //TODO add requirement conditions
        return false;
    }
    int getCost()
    {
        return cost[research_progress];
    }
    void upgrade()
    {
        science_points -= cost[research_progress];
        research_progress++;
    }
    void set_progress(int lvl)
    {
        research_progress = lvl;
    }
    void printRequirements(int yPos);
    std::string get_children_name(int c_number);
    int getChildrenHeight();
    void print();
    void render(bool is_last = false, int coord = 0);
    ~Node()
    {
        delete[] cost;
        if(children_count)
            delete[] children;
    }
};

Node technologies[TECHNOLOGIES_COUNT];

void Node::print()
{
    int temp = lvl;
    while(temp-- > 0)
        std::cout<<"->";
    std::cout<<name<<std::endl;
    for(temp = 0; temp < children_count; temp++)
    {
        technologies[children[temp]].print();
    }
}

int Node::getChildrenHeight()
{
    int answ = 25;
    if(opened)
        for(int i = 0; i < children_count; i++)
            answ += technologies[children[i]].getChildrenHeight();
    return answ;
}

std::string Node::get_children_name(int c_number)
{
    return technologies[children[c_number]].name;
}

void Node::printRequirements(int yPos)
{
    WrapTexture info_text;
    for(int i = 0; i < req_count; i++)
    {
        info_text.loadFromRenderedText("lvl " + toString(requirements[i].second) + ": " + technologies[requirements[i].first].name, BLACK, 3, false);
        info_text.render(15, 30 + yPos + 20 * i);
    }
}

void Node::render(bool is_last, int parent)
{
    bool paint = global_shift - 8 - research_tree_offset + 25 >= 0;
    if(!node_is_shifted && paint)
    {
        node_is_shifted = true;
        y_offset = -25;
    }
    if(node_is_shifted && y_offset >= SCREEN_HEIGHT - 80 - 24)
        paint = false;
    int x_offset = 10 * (lvl - 1);
    int posY = global_shift - 25 * static_cast<int>(research_tree_offset / 25.0);
    if(y_offset != global_shift - 8 && research_tree_offset % 25 != 0)
        posY -= 25;

    global_shift += 25;

    if(paint)
    {
        if(tree_render_pos_index < static_cast<int> ((SCREEN_HEIGHT - 80) / 25) + 1)
        {
            tree_render_pos[tree_render_pos_index].first = index_in_technology;
            tree_render_pos[tree_render_pos_index].second = y_offset + 80;
            tree_render_pos_index++;
        }
    }

    if(paint)
    {
        SDL_RenderDrawLine( renderer, x_offset + 5, y_offset + 8, x_offset + 25, y_offset + 8 );

        name_pic.render( x_offset + 30, y_offset);
    }

    y_offset += 25;

    if(opened)
    {
        if(paint)
        {
            SDL_RenderDrawLine( renderer, x_offset + 15, y_offset + 8 - 25, x_offset + 15, y_offset );
            open_branch.render(x_offset + 10, y_offset + 4 - 25);
        }

        int temp = children_count;
        while(temp--)
        {
            if(temp == 0)
                technologies[children[children_count - 1 - temp]].render(true, posY);
            else
                technologies[children[children_count - 1 - temp]].render();
        }
    }
    else if(children_count > 0)
        close_branch.render(x_offset + 10, y_offset + 3 - 25);

    if(is_last)
        SDL_RenderDrawLine( renderer, x_offset + 5, parent + 4, x_offset + 5, posY );
}
