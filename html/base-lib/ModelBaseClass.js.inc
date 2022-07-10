<script>
class ModelBaseClass {

	async service(param, Url) {
        let promise = await fetch(Url, {
            method: 'POST',
            headers: {
            'Accept': 'application/json',
            'Content-Type': 'application/json'
            },
            body: JSON.stringify(param) }
        )
        return promise;
    }
    
}
</script>