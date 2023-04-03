struct DrawConfig {
    unsigned int shaderProgram;
    unsigned int vao;
};

unsigned int createProgram();
DrawConfig setup();
void draw(DrawConfig);