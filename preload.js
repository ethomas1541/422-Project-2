/*
 *	Author: Gus Cochran
 *
 *	Description:
 *		Expose child process and decoder nodes to renderer.js
 *		
 *	Functions:
 *      call_cpp(command, args):
 *              runs the provided command in console with provided args
 *      
 *      decode(encoding):
 *              decodes stdout data into a string for logging
 *	History
 *		6/3/4 initial creation
 *
 * */

const {contextBridge} = require('electron');
const child_process = require('child_process');
const text_decoder = require('text-decoder')

contextBridge.exposeInMainWorld('modules', {
    call_cpp: (command, args) => {
        return new Promise((resolve, reject) => {
            var child = child_process.spawn(command, args);
             
            if(child.stdout.on("data", (data)=>{
                resolve(data);
            }));

            if(child.stderr.on("data", (data)=>{
                reject(data);
            }));

        }) ;
    },
    decode: (encoding) => {
        const td = new text_decoder()
        return td.end(encoding)
    },
});