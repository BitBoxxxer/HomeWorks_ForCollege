import { useState } from 'react'
import logo from '../assets/react.svg'

export default function Button_Count() {
  const [count, setCount] = useState(0)
  const logoAltName = `Result Alt`
  return(
    <>
    <img src={logo} alt={logoAltName}></img>
    <button
          type="button"
          className="counter"
          onClick={() => setCount((count) => count + 1)}
        >
          Count is {count}
        </button>
    </>
  )
}

/* export function Default_Time() {
    return (
        <>
        <span>Время сейчас: {'Hello'.toUpperCase}</span>
        </>
    )
} */