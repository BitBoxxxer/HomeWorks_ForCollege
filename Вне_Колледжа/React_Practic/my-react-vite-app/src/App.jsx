import reactLogo from './assets/react.svg'
import viteLogo from './assets/vite.svg'
import heroImg from './assets/hero.png'
import './App.css'
import Button_Count from './components/Butts_Counter.jsx'
import WayToTearch from './components/WayToTearch.jsx'
import {ways} from './data.js'
import Butt_Default_New from './components/Butts_Default.jsx'
import {useState} from 'react'

export default function App() {
  const stateArray = useState('Tape Butt')
  const [content, setContent] = useState('Нажмите на кнопочку')

  const differences = {
    way: 'Это про способ',
    easy: 'Это про лёгкость',
    Hello: 'Просто привет',
  };

  function handleClick(type){
        console.log (type)
        setContent(type)
    }

  return (
    <>
    <header>
      <h3>Diana's trains for Render JS</h3>
      <span>Тут будет время</span>
      <section id="spacer"></section>
    </header>
    <main>
      <Button_Count/>
      <div className="ticks">Boobs</div>
      <div className="ticks">Meow</div>
      <WayToTearch {...ways[0]}/>
      <WayToTearch {...ways[1]}/>
      <WayToTearch {...ways[2]}/>
      <WayToTearch {...ways[3]}/>
      {/* <WayToTearch title={ways.title[0]} description={ways.description[0]}/> */}
      {/* <Default_Time/> */}
      <Butt_Default_New onClickButt={() => handleClick('way')}>Way</Butt_Default_New>
      <Butt_Default_New onClickButt={() => handleClick('easy')}>EASY</Butt_Default_New>
      <Butt_Default_New onClickButt={() => handleClick('Hello')}>Hello</Butt_Default_New>

      <p>{differences[content]}</p>
    </main>
    <footer>
      <section id="spacer"></section>
    </footer>
    </>
  )
}
