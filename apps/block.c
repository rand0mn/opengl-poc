#include "block.h"
#include "register.h"


int block_set_color(struct Block *p_block, enum BlockType color_code);

struct Block block_create(
        float width,
        float height,
        float X,
        float Y,
        enum BlockType type,
        unsigned int hp,
        bool is_destroyable
) {
        struct ShaderProgram *shader = malloc(sizeof(struct ShaderProgram));
        shader_create_from_assets(shader, "shaders/block.vertex.glsl", "shaders/block.fragment.glsl", NULL);

        struct Texture2D *texture = malloc(sizeof(struct Texture2D));
        if (type == WALL) {
                texture_create_from_assets(texture, "textures/block_solid.png");
        }
        else {
                texture_create_from_assets(texture, "textures/block.png");
        }

        struct Block block;
        block.id = sequence_get_next();
        register_add(block.id, &block);

        sprite_initialize(&block.sprite, shader, texture);

        block.sprite.width = width;
        block.sprite.height = height;
        block.sprite.X = X;
        block.sprite.Y = Y;
        block.is_dead = false;

        block_set_color(&block, type);

        if (is_destroyable) {
                block.health = 0;
        }

        return block;
}

int block_render_uniform_callback(struct Sprite *p_sprite, void *context) {
        float aspect_ratio = p_sprite->width / p_sprite->height;
        shader_set_float(p_sprite->p_shader, "uTextureAspectRatio", aspect_ratio);

        return EXIT_SUCCESS;
}

int block_render(struct Block *p_block) {
        if (p_block->is_dead) {
                return EXIT_SUCCESS;
        }

        return sprite_render(&p_block->sprite, NULL, (UniformCallback) block_render_uniform_callback);
}

int block_set_color(struct Block *p_block, enum BlockType color_code) {
        switch (color_code) {
                case WALL: {
                        glm_vec4_copy((float *) &PALETTE.cabSav, p_block->sprite.color);
                        break;
                }
                case HP_1: {
                        glm_vec4_copy((float *) &PALETTE.goldTips, p_block->sprite.color);
                        break;
                }
                case HP_2: {
                        glm_vec4_copy((float *) &PALETTE.sandyBrown, p_block->sprite.color);
                        break;
                }
                case HP_3: {
                        glm_vec4_copy((float *) &PALETTE.outrageousOrange, p_block->sprite.color);
                        break;
                }
                case HP_4: {
                        glm_vec4_copy((float *) &PALETTE.fireBrick, p_block->sprite.color);
                        break;
                }
                case HP_5: {
                        glm_vec4_copy((float *) &PALETTE.cherokee, p_block->sprite.color);
                        break;
                }
                default: {
                        fprintf(stderr, "[LEVEL:INITIALIZE] -> Unknown color code %d\n", color_code);
                        glm_vec4_copy((float *) &PALETTE.transparent, p_block->sprite.color);
                        return EXIT_FAILURE;
                }
        }

        return EXIT_SUCCESS;
}
