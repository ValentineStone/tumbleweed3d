const fs = require('fs')
const path = require('path')
const child_process = require('child_process')

const cppFileRegExp = /.cpp$/
const isCppFile = file => cppFileRegExp.test(file)

const getFiles = (dir, filelist) => {
  filelist = filelist || []
  const files = fs.readdirSync(dir)
  for (const file of files) {
    const filepath = path.resolve(dir, file)
    const filestat = fs.statSync(filepath)
    if (filestat.isDirectory())
      getFiles(filepath, filelist)
    else if (isCppFile(file))
      filelist.push(filepath)
  }
  return filelist;
}

const cppFiles = getFiles('src')
const inputFiles = cppFiles.map(v => '"' + v + '"').join(' ')
const outputFile = path.resolve('build', 'tumbleweed.exe')

const command = `g++ ${inputFiles} -o ${outputFile}`

console.log({cppFiles, outputFile})
child_process.execSync(command)

