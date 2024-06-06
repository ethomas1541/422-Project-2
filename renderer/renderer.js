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
const deter_btn = document.querySelector('#deter-btn')
const invr_btn = document.querySelector('#invr-btn')
const mm_btn = document.querySelector('#mm-btn')
const rr_btn = document.querySelector('#rr-btn')
const steps = document.querySelector("#steps")


deter_btn.addEventListener('click', function(){
    console.log("deter")
    modules.call_cpp("./combined_calculator.exe", ["det"]).then(data => {
        process_results(modules.decode(data))
    }).catch(error => {
        console.log(modules.decode(error))
    });
})

invr_btn.addEventListener('click', function(){
    console.log("invr")
    modules.call_cpp("./combined_calculator.exe", ["invr"]).then(data => {
        process_results(modules.decode(data))
    }).catch(error => {
        console.log(modules.decode(error))
    });
})

mm_btn.addEventListener('click', function(){
    console.log("mm")
    modules.call_cpp("./combined_calculator.exe", ["mm"]).then(data => {
        process_results(modules.decode(data))
    }).catch(error => {
        console.log(modules.decode(error))
    });
})

rr_btn.addEventListener('click', function(){
    console.log("rr")
    modules.call_cpp("./combined_calculator.exe", ["rr"]).then(data => {
        process_results(modules.decode(data))
    }).catch(error => {
        console.log(modules.decode(error))
    });
})

function handle_empty_field(value){return 0 ? value == "" : value}

function removeAllChildNodes(parent) {
    while (parent.firstChild) {
        parent.removeChild(parent.firstChild);
    }
}
//create entries string
function call_executable(command, opcode, a_entries, b_entries){
    modules.call_cpp(command, [opcode, "3", "3", a_entries, "3", "3", b_entries]).then(data => {
        return modules.decode(data)
    }).catch(error => {
        console.log(modules.decode(error))
    });
}

function process_results(results){
    steps.innerHTML = ""
    steps.innerHTML = results
    }   

