/* 
 * File:   split.h
 * Author: antoniocs
 *
 * Created on 12 de Dezembro de 2015, 11:49
 */

#ifndef SPLIT_H
#define SPLIT_H

#ifdef __cplusplus
extern "C" {
#endif

    struct splitString {
        char **tokens;
        unsigned total;
        unsigned size;
    };

    struct splitString *split(const char *, const char *);
    void splitFree(struct splitString **);

#ifdef __cplusplus
}
#endif

#endif /* SPLIT_H */

