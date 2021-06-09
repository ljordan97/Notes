//classes
//attributes = member data, methods = member functions
//note: define methods in header, declare them in .cpp
class Song {
  std::string title;

  public: 
    void add_title(std::string new_title);

    std::string get_title();
};