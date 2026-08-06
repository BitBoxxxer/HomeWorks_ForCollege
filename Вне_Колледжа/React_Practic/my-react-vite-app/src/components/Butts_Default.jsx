import './Button.css'

export default function Butt_Default_New({children, onClickButt}){
    const handleMouseEnter = () => console.log('enter')

    return (
        <>
            <button className="ButtDefaultNew"
                    onClick={onClickButt}
                    onMouseEnter={handleMouseEnter} onDoubleClick={() => console.log('Hello')}
            >
                {children}
            </button>
        </>
    )
}