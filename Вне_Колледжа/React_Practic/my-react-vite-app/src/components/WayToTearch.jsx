export default function WayToTearch({title, description}){
  return (
    <li>
      <p>
        <strong>{title}</strong> {description}
      </p>
    </li>
  )
} /* Ну или можно указать props и потом через него образаться к переменным */